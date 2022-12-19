---
id: 647
title: 'Architektura serwerów &#8211; wydajność przetwarzania zapytań cz.2'
date: '2019-12-29T12:48:26+00:00'
author: 'Rafał Równiak'
layout: post
guid: 'http://rrowniak.com/?p=647'
permalink: /performance/architektura-serwerow-wydajnosc-przetwarzania-zapytan-cz-2/
image: /wp-content/uploads/2019/12/mike-enerio-small-unsplash.jpg
categories:
    - 'Architektura oprogramowania'
    - C
    - C++
    - Linux
    - Performance
---

Kontynuujemy nasze zmagania z przetwarzaniem zapytań. [W pierwszej części](http://rrowniak.com/architektura-oprogramowania/architektura-serwerow-wydajnosc-przetwarzania-zapytan-cz-1/) zdefiniowaliśmy problem i podjęliśmy pierwsze próby implementacji rozwiązania. Szybko jednak okazało się, że istnieją lepsze metody. Dzisiaj będziemy eksperymentować z wielowątkowością. Oczywiście nie obejdzie się bez problemów…

Kod źródłowy eksperymentów można znaleźć [tutaj](https://github.com/rrowniak/blog/tree/master/processing_pipeline).

Przejdźmy do rzeczy – ostanie wyniki pokazały, że nasz procesor się nudzi. Zapytania są niezależne więc wielowątkowość wydaje się być naturalnym remedium. Zróbmy więc tak jak robi wiele serwerów – każde zapytanie będzie obsługiwane przez osobny wątek.

Nasza (naiwna) implementacja będzie wyglądać mniej więcej tak:

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: plain; title: ; notranslate" title="">
for_each request in 100k_requests:
    create_thread(RequestProcessor::Process(request))
```

</div>Uruchamiamy więc nasz program:

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: plain; highlight: [3]; title: ; notranslate" title="">
$ ./processing_pipeline 2
Running Experiment_2_thread_per_req
Experiment interrupted - exception thrown: Resource temporarily unavailable
Only 32747 threads created
Waited 3951.76 ms, avg 25305.2 trans/sec

```

</div>Hmm… Program przerwał działanie. Widzimy, że udało się stworzyć 32 747 wątków. Prawdopodobnie nie powiodło się stworzenie kolejnego wątku. Sprawdźmy tą hipotezę:

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: plain; highlight: [10]; title: ; notranslate" title="">
$ gdb ./processing_pipeline
...
(gdb) catch throw
(gdb) run 2
...
(gdb) bt
#0  0x00007ffff78c58bd in __cxa_throw () from /usr/lib/x86_64-linux-gnu/libstdc++.so.6
#1  0x00007ffff78ee7fe in std::__throw_system_error(int) () from /usr/lib/x86_64-linux-gnu/libstdc++.so.6
#2  0x00007ffff78f0e73 in std::thread::_M_start_thread(...)
#3  0x000000000040eabe in std::thread::thread<...>(...)...
<...>
#7  0x0000000000404705 in Experiment_2_thread_per_req () at main.cpp:92
#8  0x00000000004058ce in main (argc=2, argv=0x7fffffffdcb8) at main.cpp:294
```

</div>Tak, próba stworzenia nowego obiektu `std::thread` nie powiodła się. Zapewne przekroczyliśmy jakiś limit. Pytanie tylko o jaki limit chodzi? Bo nie ma czegoś takiego jak limit wątków… W systemie Linux mamy kilka limitów które mogą ograniczać bezpośrednio lub pośrednio liczbę wątków i/lub procesów:

- Globalny limit procesów (wątek też liczony jako proces) zdefiniowany w `/proc/sys/kernel/threads-max`. U mnie ustawiony jest na:

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: plain; title: ; notranslate" title="">
$ cat /proc/sys/kernel/threads-max
513640
```

</div>- Górny limit wartości jaki może przyjąć deskryptor (pid) procesu (i wątku) zdefiniowany w `/proc/sys/kernel/pid_max`, wartość jest [obliczana przez kernel](https://elixir.bootlin.com/linux/latest/source/kernel/pid.c) na podstawie prostej formuły: 1024 \* liczba\_rdzeni \* liczba\_wątków\_per\_rdzeń.

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: plain; title: ; notranslate" title="">
$ cat /proc/sys/kernel/pid_max
32768
```

</div>- Maksymalna liczba zmapowanych obszarów pamięci w procesie (więcej tego typu limitów [tutaj](https://www.kernel.org/doc/Documentation/sysctl/vm.txt)). Limit ten można odczytać w `/proc/sys/vm/max_map_count`:

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: plain; title: ; notranslate" title="">
$ cat /proc/sys/vm/max_map_count
65530
```

</div>A co to oznacza w praktyce? Zajrzyjmy w dokumentację:

```
<pre class="wp-block-preformatted">max_map_count:

This file contains the maximum number of memory map areas a process
may have. Memory map areas are used as a side-effect of calling
malloc, directly by mmap, mprotect, and madvise, and also when loading
shared libraries.

While most applications need less than a thousand maps, certain
programs, particularly malloc debuggers, may consume lots of them,
e.g., up to one or two maps per allocation.

The default value is 65536.
```

W skrócie można powiedzieć, że licznik zmapowanych obszarów pamięci powiększa się kiedy np. ładujemy bibliotekę *so*, kiedy alokator pamięci dostaje nowy blok z kernela, bezpośrednie wywołania `mmap`, `mprotect`, `madvise`, i co dla nas najważniejsze – tworzenie wątku.

- [RLIMIT\_AS, RLIMIT\_DATA](http://man7.org/linux/man-pages/man2/getrlimit.2.html) – limit wielkości wirtualnej przestrzeni i limit segmentu danych dla procesu (zmienne zainicjowane, niezainicjowane, sterta (heap). Limity te mogą być zmieniane jednaj wartości domyślne łatwo odczytać (podobnie jak `ulimit -a` ale mamy więcej detali):

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: plain; title: ; notranslate" title="">
$ cat /proc/self/limits
Limit                     Soft Limit           Hard Limit           Units     
Max cpu time              unlimited            unlimited            seconds   
Max file size             unlimited            unlimited            bytes     
Max data size             unlimited            unlimited            bytes     
Max stack size            8388608              unlimited            bytes     
Max core file size        0                    unlimited            bytes     
Max resident set          unlimited            unlimited            bytes     
Max processes             256820               256820               processes 
Max open files            1024                 1048576              files     
Max locked memory         65536                65536                bytes     
Max address space         unlimited            unlimited            bytes     
Max file locks            unlimited            unlimited            locks     
Max pending signals       256820               256820               signals   
Max msgqueue size         819200               819200               bytes     
Max nice priority         0                    0                    
Max realtime priority     0                    0                    
Max realtime timeout      unlimited            unlimited            us 
```

</div>- Limit wynikający z braku wirtualnej pamięci dla nowych wątków. Każdy nowy wątek dostaje stos dla którego system operacyjny przydziela pewien obszar pamięci w wirtualnej przestrzeni. Obecnie dla systemów 64 bitowych stosowany jest model kanoniczny, czyli wykorzystujemy tylko 48 bitów do adresacji. Więc cała przestrzeń to 2^64. Przestrzeń użytkownika to połowa z tego – 128 TB. Szczegóły [tutaj](https://www.kernel.org/doc/Documentation/x86/x86_64/mm.txt). Z drugiej strony stos zajmuje:

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: plain; title: ; notranslate" title="">
$ ulimit -s
8192
```

</div>Co oznacza 8192 kB \* 1024 = 8388608M = 8 MB. Teoretycznie mamy miejsce w wirtualnej pamięci na 128 TB / 8 MB = 16 777 216 wątków.

- Inne limity zdefiniowane dla użytkownika jak np. `max user processes`.

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: plain; title: ; notranslate" title="">
$ ulimit -a
core file size          (blocks, -c) 0
data seg size           (kbytes, -d) unlimited
scheduling priority             (-e) 0
file size               (blocks, -f) unlimited
pending signals                 (-i) 256820
max locked memory       (kbytes, -l) 64
max memory size         (kbytes, -m) unlimited
open files                      (-n) 1024
pipe size            (512 bytes, -p) 8
POSIX message queues     (bytes, -q) 819200
real-time priority              (-r) 0
stack size              (kbytes, -s) 8192
cpu time               (seconds, -t) unlimited
max user processes              (-u) 256820
virtual memory          (kbytes, -v) unlimited
file locks                      (-x) unlimited
```

</div>Ok, uzbrojeni w pewną wiedzę teoretyczną kontynuujmy nasze śledztwo. Jak zwykle warto zobaczyć jakie funkcje systemowe zostały wywołane, ile i z jakim skutkiem:

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: plain; title: ; notranslate" title="">
$ strace -c ./processing_pipeline 2
Running Experiment_2_thread_per_req
Experiment interrupted - exception thrown: Resource temporarily unavailable
Only 32747 threads created
Waited 2993.39 ms, avg 33406.9 trans/sec
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 28.10    0.000558           0     32747           clone
 26.13    0.000519           0     32759         1 mprotect
 24.07    0.000478           0     32748           munmap
 19.18    0.000381           0     32770           mmap
  1.81    0.000036           0      3806           brk
  0.70    0.000014           0       291        18 futex
  0.00    0.000000           0         6           read
  0.00    0.000000           0         8           write
  0.00    0.000000           0         7           open
  0.00    0.000000           0         7           close
  0.00    0.000000           0         7           fstat
  0.00    0.000000           0         3           lseek
  0.00    0.000000           0         2           rt_sigaction
  0.00    0.000000           0         1           rt_sigprocmask
  0.00    0.000000           0         7         7 access
  0.00    0.000000           0         1           execve
  0.00    0.000000           0         1           getrlimit
  0.00    0.000000           0         1           arch_prctl
  0.00    0.000000           0         1           set_tid_address
  0.00    0.000000           0         1           set_robust_list
------ ----------- ----------- --------- --------- ----------------
100.00    0.001986                135174        26 total

```

</div>Widzimy, że wywołanie funkcji [`futex`](http://man7.org/linux/man-pages/man2/futex.2.html) dało negatywne rezultaty aż 18 razy. Jednak sama funkcja została wywołana tylko 291 razy co nie odpowiada ilości stworzonych wątków. Za to ciekawy trop daje nam funkcja systemowa `<a href="http://man7.org/linux/man-pages/man2/mprotect.2.html">mprotect</a>` – wywołana została 32 759 razy czyli prawie tyle co liczba naszych wątków (32 747). Ale najciekawsze jest to, że tylko jeden raz zwróciła błąd. Sprawdźmy co to za błąd:

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: plain; title: ; notranslate" title="">
$ strace -e trace=mprotect ./processing_pipeline 2 2>&1| grep "= -1"                                                                      
mprotect(0x7fa762ba1000, 4096, PROT_NONE) = -1 ENOMEM (Cannot allocate memory)
```

</div>Dokumentacja lakonicznie stwierdza:

> **ENOMEM** Internal kernel structures could not be allocated.

Ale możemy zrobić dwie rzeczy – rzucić okiem w kod źródłowy kernela albo zaryzykować hipotezę, że limit mapowania obszarów pamięci został przekroczony (`mprotect` jest wymieniana jako funkcja mogąca naruszyć ten limit). Jednak aby mieć podstawy do uznania hipotezy za prawdopodobną trzeba wykazać, że ograniczenie 65530 zostało naruszone. Więc policzmy liczbę wywołań: 32759 − 1 (*mprotect*) + 32770 (*mmap*) = 65528. Różnica może wynikać z dodatkowych czynności jak ładowanie bibliotek *so*. Przegląd kodu kernela nie daje jednoznacznej odpowiedzi ponieważ istnieje wiele ścieżek prowadzących do ENOMEM. Najciekawsze funkcje pomocnicze to [`may_expand_vm`](https://elixir.bootlin.com/linux/latest/source/mm/mmap.c#L3297), [`__vm_enough_memory`](https://elixir.bootlin.com/linux/latest/ident/__vm_enough_memory) i [`find_vma`](https://elixir.bootlin.com/linux/latest/ident/find_vma) które sprawdzają różne limity więc trudno wskazać jednoznacznie przyczynę bez głębszej analizy.

Ale jedną rzecz łatwo zrobić – mamy już hipotezę o przekroczonym limicie mapowania pamięci, liczby potwierdzają nasze przypuszczenia – pozostał więc eksperyment do wykonania – zwiększmy ten limit i zobaczmy co się stanie:

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: plain; title: ; notranslate" title="">
# echo 100000 > /proc/sys/vm/max_map_count
--------------------------------------------------
$ strace -c ./processing_pipeline 2
Running Experiment_2_thread_per_req
Experiment interrupted - exception thrown: Resource temporarily unavailable
Only 49983 threads created
Waited 3990.99 ms, avg 25056.4 trans/sec
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 30.91    0.000887           0     50007           mmap
 30.07    0.000863           0     49995         1 mprotect
 19.06    0.000547           0     49983           clone
 17.21    0.000494           0     49985           munmap
  2.75    0.000079           0      5799           brk
  0.00    0.000000           0         6           read
  0.00    0.000000           0         8           write
  0.00    0.000000           0         7           open
  0.00    0.000000           0         7           close
  0.00    0.000000           0         7           fstat
  0.00    0.000000           0         3           lseek
  0.00    0.000000           0         2           rt_sigaction
  0.00    0.000000           0         1           rt_sigprocmask
  0.00    0.000000           0         7         7 access
  0.00    0.000000           0         1           execve
  0.00    0.000000           0         1           getrlimit
  0.00    0.000000           0         1           arch_prctl
  0.00    0.000000           0       348        18 futex
  0.00    0.000000           0         1           set_tid_address
  0.00    0.000000           0         1           set_robust_list
------ ----------- ----------- --------- --------- ----------------
100.00    0.002870                206170        26 total
```

</div>Wyników chyba nie muszę komentować. Mamy przyczynę niepowodzenia. Jako ciekawostkę podam stos wywołań, który prowadzi do funkcji `mprotect`:

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: plain; highlight: [3]; title: ; notranslate" title="">
(gdb) bt
#0  0x00007ffff7050777 in mprotect () at ../sysdeps/unix/syscall-template.S:84
#1  0x00007ffff7bc24fa in allocate_stack (...) at allocatestack.c:649
#2  __pthread_create_2_1 (...) at pthread_create.c:539
#3  0x00007ffff78f0dc3 in std::thread::_M_start_thread(...) from /usr/lib/x86_64-linux-gnu/libstdc++.so.6
#4  0x000000000040eabe in std::thread::thread(...)... 
...
#8  0x0000000000404705 in Experiment_2_thread_per_req () at main.cpp:92
#9  0x00000000004058ce in main (argc=2, argv=0x7fffffffdcb8) at main.cpp:294
```

</div>Więc co teraz? Możemy manipulować limitami ale jest to bardzo zła droga w tym przypadku. Nadmierna liczba wątków negatywnie wpływa na wydajność. Trzeba to jakoś ograniczyć programowo. Najprostsze podejście może wyglądać tak:

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: python; title: ; notranslate" title="">
max_thread_limit = 100
while not done:
    thread_num = 0
    while thread_num < max_thread_limit:
        request = 100k_requests.get_next()
        create_thread(RequestProcessor::Process(request))
        thread_num++
    wait_for_all_threads()
```

</div>Odpalmy więc nasz program i zobaczmy jakie korzyści daje nam wielowątkowość:

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: plain; title: ; notranslate" title="">
./processing_pipeline 3
Running Experiment_3_thread_per_req_with_throttle for 100 threads
Control result: 6.49994e+10
Total sleep: 18920 ms, # yield: 49800, # requests: 100000
Waited 25767.7 ms, avg 3880.83 trans/sec
```

</div>**WTF??? Wynik gorszy niż w przypadku przetwarzania sekwencyjnego** opisanego w [poprzednim artykule](http://rrowniak.com/architektura-oprogramowania/architektura-serwerow-wydajnosc-przetwarzania-zapytan-cz-1/)! Dla przypomnienia:

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: plain; title: ; notranslate" title="">
$ ./processing_pipeline 1
Running Experiment_1_single_threaded
Control result: 6.49994e+10
Total sleep: 18920 ms, # yield: 49800, # requests: 100000
Waited 23612.7 ms, avg 4235 trans/sec
```

</div>Czyli teraz mamy ponad 25 sekund! Co z tą wielowątkowością?

Otóż powyższy przykład pokazuje jak nieumiejętne korzystanie z tego narzędzia przynosi więcej szkód niż pożytku. Celowo pokazałem jakie problemy z limitami możemy napotkać. Niestety często podczas testów możemy tych problemów nie zauważyć gdyż same limity są dość wysoko ustawione a analiza takich zdarzeń może być trudna. Jak zwykle poinformuje nas o problemach niespecjalnie szczęśliwy klient. Druga sprawa to ślepa wiara w sprawczą moc wielowątkowości. Nasze zrównoleglenie nie pomogło, a przynajmniej nie to naiwne podejście. W kolejnej części zobaczymy co poszło nie tak i gdzie jest problem. Zobaczymy też jak można usprawnić nasz algorytm aby wielowątkowość okazała się skuteczna.