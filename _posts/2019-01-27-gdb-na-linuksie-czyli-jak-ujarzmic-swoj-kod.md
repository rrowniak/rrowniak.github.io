---
id: 499
title: 'gdb na Linuksie czyli jak ujarzmić swój kod'
date: '2019-01-27T10:33:43+00:00'
author: 'Rafał Równiak'
layout: post
guid: 'http://rrowniak.com/?p=499'
permalink: /programming/gdb-na-linuksie-czyli-jak-ujarzmic-swoj-kod/
image: /wp-content/uploads/2019/01/mohsen-bagherzadeh-451137-small.jpg
categories:
    - 'Dobre praktyki'
    - Linux
    - Programming
---

`gdb` jest chyba najbardziej przerażającym narzędziem dla początkujących programistów, a jeśli dodać, że najczęściej w naturze występuje na systemach Linux to niejedna tęga głowa dostaje palpitacji serca. Ale jeśli kodujesz w C lub C++ na systemy Linuksowe to niestety jesteś skazany na ten debugger. Ale nie taki diabeł straszny jak go malują. Zobaczmy na przykładzie jak korzystać z tego narzędzia…

`gdb` jest debuggerem pracującym w trybie tekstowym, czyli nie ma trybu graficznego gdzie moglibyśmy sobie klikać i oglądać ładne okienka. Jednak nie jest to w żaden sposób ograniczające, wręcz przeciwnie – `gdb`to bardzo potężne narzędzie, chyba najbardziej rozbudowany debugger. I wiele środowisk programistycznych pod spodem wykorzystuje właśnie ten debugger. Są również graficzne nakładki. My jednak będziemy zapoznawać się z `gdb`bez używania takich dobrodziejstw.

## Przykład

Zaczniemy od przykładu, programu, który będzie wyświetlał prędkość zadanego rdzenia CPU, z błędami na potrzeby naszych ćwiczeń oczywiście. Dla przykładu:

`$ ./cpu_speed 2`

zwróci nam wynik:

`799.980 MHz`

A oto pierwsza próba zaimplementowania tego programu (wszystkie wersje można znaleźć na [moim githubie](https://github.com/rrowniak/blog/tree/master/gdb-exercise)):

```
<pre class="wp-block-code">```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char filename[] = "/proc/cpuinfo";
const char cpu_section[] = "processor\t: %d";
const char speed_tag[] = "cpu MHz\t\t: ";

static int is_cpu_section(const char* section_line, const char* curr_line) {
    do {
        if (*section_line == '\0') {
            return 1;
        }
    } while (curr_line != '\0' && *section_line == *curr_line);
    return 0;
}

static const char* extract_mhz(const char* line)
{
    const char* str = NULL;
    if ((str = strstr(line, speed_tag)) != NULL) {
        str += strlen(speed_tag);
    }
    return str;
} 

static void scan_file(FILE *f, const char* cpu_section_num)
{
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int section_found = 0;
    const char* mhz = NULL; 

    while ((read = getline(&line, &len, f)) != -1) {
        if (!section_found && !is_cpu_section(cpu_section_num, line)) {
            section_found = 1;
            continue;
        }

        if ((mhz = extract_mhz(line)) != NULL) {
            printf("%s MHz", mhz);
            break;
        }
    }

    if (line) {
        free(line);
    }
}

int main(int argc, char const *argv[])
{
    FILE* f = NULL;
    int core_num;
    char cpu_section_num[255];

    if (argc < 2) {
        fprintf(stderr, "usage: cpu_speed <cpu_num>\n");
        exit(EXIT_FAILURE);
    }

    core_num = atoi(argv[1]);
    sprintf(cpu_section_num, cpu_section, core_num);

    scan_file(f, cpu_section_num);

    fclose(f);
    return EXIT_SUCCESS;
}
```
```

Kod oczywiście kompilujemy:

`$ gcc -o2 cpu_speed-v1.c -o cpu_speed-v1`

i uruchamiamy. Niestety rezultat jest trochę inny niż ten oczekiwany:

`$ ./cpu_speed-v1 3<br></br> Segmentation fault (core dumped)`

W skrócie można powiedzieć, że `Segmentation fault` to błąd dostępu do pamięci, odwołujemy się pod adres, który (z różnych powodów) jest dla nas niedostępny. I co teraz? Można oczywiście wrzucić kod na jakieś forum np. [tutaj](https://4programmers.net/) i liczyć, że jakaś pomocna dusza znajdzie rozwiązanie problemu. Ale szczerze mówiąc – nie wypada, a przynajmniej nie wypada aby samemu nie spróbować zdiagnozować usterki. I tu do akcji wkracza `gdb`.

## Pierwszy krok – start `gdb`

Odpalmy więc naszego odpluskwiacza poleceniem:

`$ gdb ./cpu_speed`

Zostaniemy przywitani konsolą `gdb`, nasze pierwsze polecenie to uruchomienie programu z argumentem: `run 2`. Jako rezultat dostaniemy coś takiego:

```
<pre class="wp-block-code">```
(gdb) run 1
Starting program: /home/rr/tmp/cpu_speed-v1 1

Program received signal SIGSEGV, Segmentation fault.
_IO_getdelim (lineptr=0x7fffffffdc18, n=0x7fffffffdc20, delimiter=10, fp=0x0) at iogetdelim.c:52
52	iogetdelim.c: No such file or directory.
```
```

No cóż, póki co nie wiele nam to mówi, ale możemy wyczytać, że nasz program otrzymał sygnał `SIGSEV`co właśnie oznacza `Segmentation fault`, mamy adresy pewnych zmiennych i ostrzeżenie, że nie można otworzyć pewnego pliku. Ten plik to część biblioteki standardowej C więc można podejrzewać, że tam został naruszony dostęp do pamięci. Ale nie oznacza to, że tam jest błąd, najprawdopodobniej to my przekazaliśmy złe argumenty do jakiejś funkcji z biblioteki C. Aby to zrobić musimy sprawdzić stos wywołań (*call stack*) poleceniem `bt` co jest skrótem od *backtrace*

```
<pre class="wp-block-code">```
(gdb) bt
#0  _IO_getdelim (lineptr=0x7fffffffdc18, n=0x7fffffffdc20, delimiter=10, fp=0x0) at iogetdelim.c:52
#1  0x000000000040093b in scan_file ()
#2  0x0000000000400a29 in main ()
```
```

Widzimy, że w całą kabałę jest zamieszana funkcja `scan_file`ale przecież nie wywołujemy nic takiego jak `_IO_getdelim`, o co więc chodzi? Możemy przyjrzeć się bliżej co się dzieje w `scan_file`zmieniając aktywną ramkę numer 0 na numer 1 (odpowiada funkcji `scan_file`) poleceniem `f 1` (`f`to skrót od *frame*):

```
<pre class="wp-block-code">```
(gdb) f 1
#1  0x000000000040093b in scan_file ()
```
```

i spróbujmy zapytać debugger o konkretną linię kodu poleceniem `l`(*list*):

```
<pre class="wp-block-code">```
(gdb) l
47	in iogetdelim.c
```
```

Hmm…

## Kompilacja w trybie *debug*

Coś jest nie tak. Taki potężny debugger, a nie dostaliśmy żadnych wartościowych danych? Okazuje się, że jest to bardzo częsta pułapka, w którą wpadają początkujący adepci sztuki programowania. Problemem nie jest debugger, tylko sposób w jaki skompilowaliśmy naszą aplikację – użyliśmy opcji `-o2`nakazując naszemu kompilatorowi wykonanie agresywnych optymalizacji. A trzeba wiedzieć, że debugger potrzebuje dodatkowych informacji, pewnych metadanych zaszytych w pliku wykonywalnym aby móc dostarczyć nam więcej szczegółów. Więc trzeba powiedzieć naszemu kompilatorowi aby umieścił te informacje – robimy to poleceniem `-g`. Wyłączymy również agresywne optymalizacje aby nie doświadczać potencjalnie dziwnych zachowań podczas debugowania (np. brak zmienny lokalnych, brak pewnych wywołań itp.). A i chyba najważniejsze polecenie – z `gdb`wychodzimy poleceniem `q`. Więc kompilujemy od nowa:

`gcc -g cpu_speed-v1.c -o cpu_speed-v1_debug`

I ponawiamy nasze eksperymenty. Polecenie `bt`jest już o wiele bardziej przydatne:

```
<pre class="wp-block-code">```
(gdb) bt
#0  _IO_getdelim (lineptr=0x7fffffffdc08, n=0x7fffffffdc10, delimiter=10, fp=0x0) at iogetdelim.c:52
#1  0x000000000040093b in scan_file (f=0x0, cpu_section_num=0x7fffffffdc60 "processor\t: 1") at cpu_speed-v1.c:35
#2  0x0000000000400a29 in main (argc=2, argv=0x7fffffffde58) at cpu_speed-v1.c:66
```
```

Wiemy już, że problem jest w *cpu\_speed-v1.c,* linia 35, niech debugger pokaże więcej szczegółów:

```
<pre class="wp-block-code">```
(gdb) f 1
#1  0x000000000040093b in scan_file (f=0x0, cpu_section_num=0x7fffffffdc60 "processor\t: 1") at cpu_speed-v1.c:35
35	    while ((read = getline(&line, &len, f)) != -1) {
```
```

Aha, tu jest problem, ale jaki dokładnie? Może czas na podejrzenie wartości zmiennych? Nic trudnego, polecenie `p`jest do tego stworzone:

```
<pre class="wp-block-code">```
(gdb) p line
$1 = 0x0
(gdb) p len
$2 = 0
(gdb) p f
$3 = (FILE *) 0x0
```
```

Zmienna `line`i `len`mogą przyjmować takie wartości podczas pierwszej iteracji pętli `while`ale `f`nie może przyjmować wartości `0`czyli `NULL`! Więc robimy przegląd kodu i co się okazuje? Przecież wskaźnik `f`jest tylko inicjowany a brakuje funkcji `fopen()`! Co za błąd, ja biorę się za poprawianie a tymczasem zobaczmy czego już się nauczyliśmy:

## Ściąga

<div class="wp-block-advgb-list">- `gdb ./nazwa_programu`– rozpoczęcie sesji debuggera
- `run argument_1 argument_2 ...`– uruchomienie naszego programu pod kontrolą debuggera
- `bt`– wyświetlenie aktualnego stosu wywołań (*callstack*)
- `f mumer_ramki`– wybór aktywnej ramki (funkcji w stosie wywołań)
- `p nazwa_zmiennej`– wypisanie wartości danej zmiennej. Uwaga – zmienna musi być widoczna w danym bloku (*scope*)
- `l`– zobacz bieżącą linijkę i sąsiadujący kod
- `q`– tym poleceniem wychodzimy z debuggera (kończymy sesję)
- Aby debuggowanie było łatwe i przyjemne należy skompilować kod jako *debug* czyli w `gcc`dodajemy opcję `-g`

<style>.advgblist-041b7e80-3aad-408d-b963-7186202dd0d8 li { font-size: 16px; margin-left: 20px }</style><style>.advgblist-041b7e80-3aad-408d-b963-7186202dd0d8 li:before {
                            font-size: 16px;
                            color: #000;
                            line-height: 18px;
                            margin: 2px;
                            padding: 2px;
                            margin-left: -22px;
                        }</style></div>## Tryb krokowy

Kod poprawiony, poniższa wstawka dodana:

```
<pre class="wp-block-code">```c
    if ((f = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "can't open %s file", filename);
        exit(EXIT_FAILURE);
    }
```
```

Kompilujemy i testujemy… I znowu coś nie jest w porządku! Tym razem nasz program uruchamia się i nie chce zakończyć działania. Podejrzewamy pętlę nieskończoną. Odpalmy sesję `gdb`w taki sam sposób jak poprzednio. I dziwna sytuacja – `gdb` nie daje nam interaktywnej konsoli. Czyżby debugger również się zapętlił? Na szczęście nie. Uruchomiliśmy program, a `gdb`nie widzi potrzeby jago przerywania (bo np. nie ma sygnału `SIGSEV`). Więc musimy zrobić to sami poleceniem `Ctrl + C`:

```
<pre class="wp-block-code">```
(gdb) run 1
Starting program: /home/rr/tmp/cpu_speed-v2_debug 1
^C
Program received signal SIGINT, Interrupt.
0x00000000004008d2 in is_cpu_section (section_line=0x7fffffffdc60 "processor\t: 1", curr_line=0x602240 "processor\t: 0\n") at cpu_speed-v2.c:14
14	    } while (curr_line != '\0' && *section_line == *curr_line);
(gdb) bt
#0  0x00000000004008d2 in is_cpu_section (section_line=0x7fffffffdc60 "processor\t: 1", curr_line=0x602240 "processor\t: 0\n") at cpu_speed-v2.c:14
#1  0x0000000000400978 in scan_file (f=0x602010, cpu_section_num=0x7fffffffdc60 "processor\t: 1") at cpu_speed-v2.c:36
#2  0x0000000000400b01 in main (argc=2, argv=0x7fffffffde58) at cpu_speed-v2.c:71
```
```

Widzimy, że kombinacja `Ctrl + C`wygenerowała sygnał `SIGINT`(*interrupt*) i to spowodowało zatrzymanie naszego programu i przejście do interaktywnej sesji. Od razu wyświetliłem stos wywołań poleceniem `bt`i widzimy, że łańcuch wywołań to `main`-&gt; `scan_file`-&gt; `is_cpu_section`a w środku tej ostatniej funkcji mamy pętlę `do-while`. I właśnie tutaj zaczynamy podejrzewać, że coś jest nie tak. Możemy spróbować przeanalizować kod lub skorzystać z jeszcze innej możliwości. A mianowicie chcielibyśmy przeanalizować jak do tego doszło, że warunki wyjścia z pętli nigdy nie są spełnione. Spróbujemy przeanalizować działanie naszego programu w sposób krokowy, linia za linią. Ale aby to zrobić musimy ustawić pułapkę, czyli miejsce w którym debugger automatycznie się zatrzyma abyśmy mogli ręcznie kontynuować wykonanie programu. Do tego służą tzw. *breakpoint’y*. Ustawmy się taki przed wywołaniem funkcji `is_cpu_section`– chodzi oczywiście o plik *cpu\_speed-v2.c* linię 36. Do tego służy polecenie `b`:

```
<pre class="wp-block-code">```
(gdb) b cpu_speed-v2.c:36
Breakpoint 1 at 0x40095f: file cpu_speed-v2.c, line 36.
```
```

I ponownie uruchommy nasz program poleceniem `run 2`:

```
<pre class="wp-block-code">```
(gdb) run 2
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/rr/tmp/cpu_speed-v2_debug 2

Breakpoint 1, scan_file (f=0x602010, cpu_section_num=0x7fffffffdc60 "processor\t: 2") at cpu_speed-v2.c:36
36	        if (!section_found && !is_cpu_section(cpu_section_num, line)) {
```
```

Świetnie, nasza pułapka zadziałała więc teraz możemy przeglądać zmienne i krokowo kontynuować działanie programu, do tego mamy trzy polecenia:

<div class="wp-block-advgb-list">- `n`– wykonaj bieżącą linię (polecenie)
- `s`– wejdź do funkcji jeśli takie wywołanie jest w bieżącej linii
- `c`– wyjdź z trybu manualnego i kontynuuj działanie programu (aż do następnej pułapki bądź `Ctrl + C`)

<style>.advgblist-debaed5f-f9de-491a-bb69-bd05f7a862ae li { font-size: 16px; margin-left: 20px }</style></div>Tutaj można zobaczyć te polecenia w akcji:

```
<pre class="wp-block-code">```
(gdb) s
is_cpu_section (section_line=0x7fffffffdc60 "processor\t: 2", curr_line=0x602240 "processor\t: 0\n") at cpu_speed-v2.c:11
11	        if (*section_line == '\0') {
(gdb) n
14	    } while (curr_line != '\0' && *section_line == *curr_line);
(gdb) p *section_line
$1 = 112 'p'
(gdb) p *curr_line
$2 = 112 'p'
(gdb) n
11	        if (*section_line == '\0') {
(gdb) n
14	    } while (curr_line != '\0' && *section_line == *curr_line);
(gdb) p *section_line
$3 = 112 'p'
(gdb) p *curr_line
$4 = 112 'p'
```
```

Widać wyraźnie, że podczas dwóch iteracji pętli `do-while`wskaźniki `section_line`i `curr_line`nadal wskazują na te same wartości! Czyli warunek zawsze będzie ten sam! Mamy kolejny błąd. Poprawmy go zatem na:

```
<pre class="wp-block-code">```c
static int is_cpu_section(const char* section_line, const char* curr_line) {
    do {
        if (*section_line == '\0') {
            return 1;
        }
    } while (curr_line != '\0' && *section_line++ == *curr_line++);
    return 0;
}
```
```

Zdecydowanie lepiej. Program działa:

```
<pre class="wp-block-code">```
$ ./cpu_speed-v3_debug 3
810.632
 MHz
```
```

Chociaż tekst nie jest idealnie złożony, gdzieś pojawiło się niepotrzebne złamanie linii… Ale ten problem już zostawiam jako zadanie domowe.

## Co udało się omówić?

- [Przykład](#advgb-toc-24c8a292-4116-40cc-8ce8-55b00f8e9519)
- [Pierwszy krok – start gdb](#advgb-toc-37bdb69d-6878-4702-bf56-e71bdc2016fe)
- [Kompilacja w trybie debug](#advgb-toc-448e4f80-2913-4063-ba81-544c6878d156)
- [Ściąga](#advgb-toc-c88e8b58-9f51-485c-a93b-b1789b801d05)
- [Tryb krokowy](#advgb-toc-ab9448ec-51fe-4c1c-93f1-477f936b9e3c)
- [Co udało się omówić?](#advgb-toc-7f5fa526-04eb-406d-ab69-39fedc2b9ccb)