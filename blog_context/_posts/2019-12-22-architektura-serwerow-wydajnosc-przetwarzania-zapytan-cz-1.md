---
id: 631
title: 'Architektura serwerów &#8211; wydajność przetwarzania zapytań cz.1'
date: '2019-12-22T08:09:51+00:00'
author: 'Rafał Równiak'
layout: post
guid: 'http://rrowniak.com/?p=631'
permalink: /programming/architektura-serwerow-wydajnosc-przetwarzania-zapytan-cz-1/
image: /wp-content/uploads/2019/12/ming-lv-small-unsplash.jpg
categories:
    - 'Architektura oprogramowania'
    - C
    - C
    - C++
    - C++
    - 'Dobre praktyki'
    - Linux
    - Performance
    - Programming
---

Ten wpis rozpoczyna krótką serię na temat architektury serwerów. Będzie to analiza różnych podejść skupiająca się na badaniu wydajności poszczególnych taktyk. Eksperymenty będą wykonywane na systemie Linux z użyciem różnych narzędzi jak np. Intel VTune, perf, dtrace itp. Pokażę różnorakie triki aby wydobyć poszczególne metryki. Artykuły będą raczej trudne, przydatne głownie dla programistów i inżynierów zajmujących się tematyką wydajności aplikacji sieciowych i serwerowych.

### Wstęp

Zająłem się tą tematyką z dwóch powodów. Po pierwsze temat ten obrósł w liczne mity, które często są powtarzane w środowisku inżynierskim przy porannej kawie. Więc najwyższy czas obalić pewne mylne wyobrażenia takie jak np. *zawsze wielowątkowość przyspiesza*, *optymalizacje to samo zło*, *prędkość = więcej ramu*, *aby coś przyspieszyć musisz poznać więcej ficzerów danego języka*, *kopiowanie spowalnia* itp.

Drugi powód to fakt, że przymierzam się do pewnego projektu open-source, gdzie tego typu zagadnienia to chleb powszedni. Więc warto nieco poeksperymentować w kontrolowanym środowisku i przy okazji podzielić się wynikami.

### Eksperyment

Zdefiniujmy problem. Mamy do przetworzenia 100 tys. niezależnych zapytań. Dla uproszczenia problematyki każde zapytanie składa się tylko z identyfikatora i generowanie polega na zwiększaniu wartości o jeden:

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: cpp; title: ; notranslate" title="">
bool RequestGenerator::GetNext(Request& req)
{
    req.id = current++;

    if (current > N) {
        return false;
    }

    return true;
}
```

</div>Każde zapytanie zostanie przetworzone zgodnie z poniższą procedurą:

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: cpp; title: ; notranslate" title="">
void RequestProcessor::Process(const Request& req, Response& r) const
{
    cnt_requests.inc();
    
    auto tmp = req.id * 13;
    double tmpd = static_cast<double>(tmp);
    tmpd = sqrt(tmpd*tmpd + 3.1415 * sin(tmpd * 2 * M_1_PI));
    snprintf(r.text, RespTextSize, "Resp: %f", tmpd);
    r.result = tmpd;
    r.req = req;

    // simulate io operations
    using namespace std::chrono_literals;

    if (req.id % 10000 == 0) {
        cnt_sleep_total.inc_by(1000);
        
        // IOBegin();
        std::this_thread::sleep_for(1s);
        // IOEnd();
    } else if (req.id % 1000 == 0) {
        cnt_sleep_total.inc_by(88);
        
        // IOBegin();
        std::this_thread::sleep_for(88ms);
        // IOEnd();
    } else if (req.id % 500 == 0) {
        cnt_sleep_total.inc_by(10);
        
        // IOBegin();
        std::this_thread::sleep_for(10ms);
        // IOEnd();
    } else if (req.id % 2 == 0) {
        cnt_yield.inc();
        
        // IOBegin();
        std::this_thread::yield();
        // IOEnd();
    }

    // do some copying and text transformations
    r.textSize = std::min(data.size(), RespTextSize);
    std::copy_n(std::begin(data), r.textSize, r.text);
    // replace "v" with "V"
    std::replace(std::begin(r.text), std::begin(r.text) + r.textSize, 'v', 'V');
}
```

</div>Powyższy kod nie robi nic użytecznego. Został on zdefiniowany specjalnie na potrzeby tego eksperymentu. Mamy więc kilka obliczeń zmiennoprzecinkowych, operacje na większym bloku tekstu – `r.textSize` wynosi 12386 bajtów, kopiowanie bloku pamięci i wywoływanie funkcji systemowych poprzez funkcje z biblioteki standardowej `std::this_thread::sleep_for()` i `std::this_thread::yield()` które to mają symulować operacje IO (np. odczyt z dysku, zapytanie do bazy danych, itp) i przełączanie kontekstu (*context switching*). Jak to w praktyce bywa, operacje IO bywają kapryśne toteż nasza procedura wywołuje je z różną częstotliwością. Nie będziemy optymalizować tego kodu – nie taka jest idea.

Powyższy eksperyment ma za zadanie symulować zadania z jakimi może spotkać się serwer aplikacji (np. serwer http, zmq, procesor transakcji itp).

Naszym zadaniem jest wykonać 100 tysięcy zapytań (czyli 100 tysięcy wywołań powyższej procedury) w jak najszybszym czasie.

Testy będę przeprowadzał na maszynie wyposażonej w procesor Intel Core i7-6820HK CPU @ 2.70GHz i 64 GB pamięci RAM.

Pełny kod źródłowy z eksperymentami dostępny jest [tutaj](https://github.com/rrowniak/blog/tree/master/processing_pipeline).

### Rozwiązanie 1

Najprostsze rozwiązanie to sekwencyjne procesowanie zapytań jak w poniższym pseudokodzie:

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: plain; title: ; notranslate" title="">
for_each request in 100k_requests:
    RequestProcessor::Process(request)
```

</div>Implementacja taka jest bardzo prosta i chyba zawsze warto od tego zacząć co najmniej z kilku powodów: prostsza implementacja – mniej błędów, dostaniemy początkowe wyniki do późniejszego porównania, sekwencyjna, jednowątkowa implementacja jest łatwa do badania i profilowania.

Wykonanie takiego programu daje następujące rezultaty:

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: plain; title: ; notranslate" title="">
$ /usr/bin/time -v ./processing_pipeline 1
Running Experiment_1_single_threaded
Control result: 6.49994e+10
Total sleep: 18920 ms, # yield: 49800, # requests: 100000
Waited 24367.9 ms, avg 4103.76 trans/sec
	Command being timed: "./processing_pipeline 1"
	User time (seconds): 5.39
	System time (seconds): 0.02
	Percent of CPU this job got: 22%
	Elapsed (wall clock) time (h:mm:ss or m:ss): 0:24.36
	Average shared text size (kbytes): 0
	Average unshared data size (kbytes): 0
	Average stack size (kbytes): 0
	Average total size (kbytes): 0
	Maximum resident set size (kbytes): 3984
	Average resident set size (kbytes): 0
	Major (requiring I/O) page faults: 0
	Minor (reclaiming a frame) page faults: 147
	Voluntary context switches: 201
	Involuntary context switches: 39
	Swaps: 0
	File system inputs: 0
	File system outputs: 0
	Socket messages sent: 0
	Socket messages received: 0
	Signals delivered: 0
	Page size (bytes): 4096
	Exit status: 0
```

</div>Pierwsze trzy linijki to informacje podane przez sam program wykonujący eksperyment:

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: plain; title: ; notranslate" title="">
Running Experiment_1_single_threaded
Control result: 6.49994e+10
Total sleep: 18920 ms, # yield: 49800, # requests: 100000
Waited 24367.9 ms, avg 4103.76 trans/sec
```

</div>Najważniejsze informacje to sumaryczny czas spędzony w funkcji *sleep* (~19s) i ilość wywołań funkcji *yield*. Czyli wykonując sekwencyjnie wszystkie zapytania (100k) program będzie się wykonywał co najmniej 18 920 milisekund. Potem mamy zmierzony czas eksperymentu i wynosi on ok 24 sekundy. I dalej mamy podaną średnią liczbę transakcji wykonanych w czasie jednej sekundy – ~4104 transakcje na sekundę. Na podstawie tych podstawowych informacji możemy powiedzieć, że program spał 18 920 ms a robił „*coś* innego” przez 5 448 ms.

Przeanalizujmy dalsze wyniki wygenerowane przez program `/usr/bin/time`, który w odróżnieniu od swojego „*kuzyna*” czyli komendy `time` (wbudowanej w interpreter `shell`) podaje dużo ciekawych szczegółów.

Linia `User time (seconds): 5.39` mówi nam, że program spędził w `userspace` ok 5.4 sekundy co sugeruje, że nasze „*coś innego*” to w całości nasz kod a nie np. wykonanie procedur jądra systemu na nasze żądanie (taki czas został oszacowany na `System time (seconds): 0.02`).

Można zaryzykować hipotezę, że przez 5.39 + 0.02 sekundy nasz program intensywnie obciążał jeden rdzeń procesora a przez 18.92 sekundy nic nie robił. Spróbujmy zatem obliczyć eksperymentalnie średnie zużycie procesora: (5.39 + 0.02) / 24.36 = ~22.2 %. Aby zweryfikować naszą hipotezę wystarczy rzucić okiem na zmierzone zużycie procesora `Percent of CPU this job got: 22%`. Po tych krótkich spostrzeżeniach wiemy, że nie wykorzystujemy w pełni naszego procesora. Innymi słowy – da się szybciej.

Zanim przejdziemy do dalszych usprawnień naszego programu, zróbmy kilka pomiarów które pozwolą nam obejrzeć program od innej strony. Zobaczmy jakie funkcje systemowe były wywoływane przez nasz program:

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: plain; title: ; notranslate" title="">
$ strace -c  ./processing_pipeline 1
Running Experiment_1_single_threaded
Control result: 6.49994e+10
Total sleep: 18920 ms, # yield: 49800, # requests: 100000
Waited 26401.5 ms, avg 3787.67 trans/sec
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
100.00    0.000474           0     49800           sched_yield
  0.00    0.000000           0         6           read
  0.00    0.000000           0         4           write
  0.00    0.000000           0         7           open
  0.00    0.000000           0         7           close
  0.00    0.000000           0         7           fstat
  0.00    0.000000           0         3           lseek
  0.00    0.000000           0        19           mmap
  0.00    0.000000           0        11           mprotect
  0.00    0.000000           0         1           munmap
  0.00    0.000000           0         3           brk
  0.00    0.000000           0         2           rt_sigaction
  0.00    0.000000           0         1           rt_sigprocmask
  0.00    0.000000           0         7         7 access
  0.00    0.000000           0       200           nanosleep
  0.00    0.000000           0         1           execve
  0.00    0.000000           0         1           getrlimit
  0.00    0.000000           0         1           arch_prctl
  0.00    0.000000           0         2           futex
  0.00    0.000000           0         1           set_tid_address
  0.00    0.000000           0         1           set_robust_list
------ ----------- ----------- --------- --------- ----------------
100.00    0.000474                 50085         7 total

```

</div>Wywołania `sched_yield` i `nanosleep` nie powinny dziwić. Jednak jedna rzecz może zastanawiać – funkcja systemowa `access` (sprawdza uprawnienia) była wywoływana siedem razy i za każdym razem zwracała błąd. Należy zwracać uwagę na tego typu sytuacje ponieważ mogą się przyczyniać do znacznego spadku wydajności. Często jest tak, że błędy są „naprawiane” i użytkownik nie widzi nic oprócz spadku wydajności.

Przyjrzyjmy się zatem bliżej wywołaniom tej funkcji:

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: plain; title: ; notranslate" title="">
$ strace -T -e trace=access  ./processing_pipeline 1                                                                                        
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory) <0.000173>
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory) <0.000129>
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory) <0.000052>
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory) <0.000029>
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory) <0.000027>
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory) <0.000027>
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory) <0.000027>

```

</div>Okazuje się, że jest to sprawka *glibc*, który robi to celowo:

> **`/etc/ld.so.nohwcap`** When this file is present the dynamic linker will load the non-optimized version of a library, even if the CPU supports the optimized version.
> 
> <cite>[Debian `glibc` manpage for `ld.so`](https://anonscm.debian.org/cgit/pkg-glibc/glibc.git/tree/debian/local/manpages/ld.so.8)</cite>

Czas spędzony na tych wywołaniach jest znikomy (nawiasy &lt;&gt;). Fałszywy alarm.

Jest jeszcze jedna rzecz, którą musimy zbadać – co tak na prawdę robi nasz kod?

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: plain; title: ; notranslate" title="">
$ perf record  ./processing_pipeline 1
```

</div>A po wykonaniu:

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: plain; title: ; notranslate" title="">
$ perf report
```

</div>Wyświetli się interaktywna konsola profilera:

<figure class="wp-block-image size-large">![](https://i0.wp.com/rrowniak.com/wp-content/uploads/2019/12/image.png?resize=696%2C422)</figure>I już na pierwszy rzut oka widać, że najdroższa operacja pod względem zużycia CPU to modyfikacja tekstu. Niestety jest to część, której nie możemy dotykać więc nasze możliwości usprawnień zostały wyczerpane.

W [następnych](http://rrowniak.com/c-2/architektura-serwerow-wydajnosc-przetwarzania-zapytan-cz-2/) odsłonach spróbujemy zrównoleglić nasze przetwarzanie zapytań. Wydawać by się mogło, że spawa jest banalnie prosta. Okazuje się, że istnieje wiele podejść do tego tematu, każde z nich dotyka pewnych subtelnych niuansów. Będziemy odkrywać różne pułapki i przekonamy się, że wybór złej taktyki daje zaskakująco podłe wyniki.