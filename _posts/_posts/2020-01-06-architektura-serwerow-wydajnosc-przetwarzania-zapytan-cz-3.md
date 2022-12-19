---
id: 660
title: 'Architektura serwerów – wydajność przetwarzania zapytań cz.3'
date: '2020-01-06T12:43:49+00:00'
author: 'Rafał Równiak'
layout: post
guid: 'http://rrowniak.com/?p=660'
permalink: /performance/architektura-serwerow-wydajnosc-przetwarzania-zapytan-cz-3/
image: /wp-content/uploads/2019/12/alessio-furlan-small-unsplash.jpg
categories:
    - 'Architektura oprogramowania'
    - C
    - C++
    - Linux
    - Performance
---

[Ostatnio](http://rrowniak.com/c-2/architektura-serwerow-wydajnosc-przetwarzania-zapytan-cz-2/) udało nam się zrównoleglić przetwarzanie naszych zapytań. Jednak wydajność tego rozwiązania okazała się mocno rozczarowująca. Dzisiaj sprawdzimy co nie zagrało i jak przybliżyć rezultaty do oczekiwań. Użyjemy narzędzia VTune od Intela – od niedawna można z niego korzystać za darmo.

Przypomnijmy co do tej pory zrobiliśmy:

- [Cześć pierwsza](http://rrowniak.com/architektura-oprogramowania/architektura-serwerow-wydajnosc-przetwarzania-zapytan-cz-1/) to definicja problemu i testy implementacji przetwarzającej zapytania w sposób sekwencyjny.
- [Część druga](http://rrowniak.com/c-2/architektura-serwerow-wydajnosc-przetwarzania-zapytan-cz-2/) to nasze zmagania z przetwarzaniem wielowątkowym. Natrafiliśmy na szereg problemów i zagadnień.
- [Kod źródłowy](https://github.com/rrowniak/blog/tree/master/processing_pipeline).

Nasz eksperyment zakończył się mocno ograniczonym sukcesem – implementacja wielowątkowa jest wolniejsza od sekwencyjnego przetwarzania. Coś co nie miało prawa się wydarzyć. Rzućmy okiem na kod, który realizuje to przetwarzanie:

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: cpp; highlight: [25,35]; title: ; notranslate" title="">
    MaxThreadNum = 100;    
    RequestGenerator gen{SampleN};
    Timer t{SampleN};
    Request r;
    double sum = 0;
    RequestProcessor p{filename};
    RequestProcessor::ResetCounter();

    bool in_progress = true;

    std::vector<std::thread> tasks;
    tasks.reserve(MaxThreadNum);

    std::vector<std::future<Response>> futures;
    futures.reserve(MaxThreadNum);

    while (in_progress) {
        futures.clear();
        tasks.clear();

        size_t i = 0;
        for (; i < MaxThreadNum && gen.GetNext(r); ++i) {
            std::promise<Response> promises;
            futures.push_back(promises.get_future());
            tasks.emplace_back(Experiment_2_task, r, p, std::move(promises));
        }

        in_progress = (i == MaxThreadNum);

        for (auto& f : futures) {
            sum += f.get().result;
        }

        for(auto& task : tasks) {
            task.join();
        }
    }

    std::cout << "Control result: " << sum << "\n";
```

</div>W skrócie – wykonujemy zapytania w paczkach, jednorazowo pakujemy `MaxThreadNum` zapytań, dla każdego tworzymy nowy wątek, a potem czekamy aż wszystkie zapytania w paczce zostaną przetworzone. I powtarzamy czynność aż przetworzymy wszystkie zapytania.

Przed wykonaniem pomiarów możemy się zastanowić co może powodować takie słabe rezultaty. Dla każdego zapytania tworzymy nowy wątek (linia 24) – to może być kosztowne. Druga, potencjalnie kosztowna, operacja to linia 34 czyli czekanie na zakończenie przetwarzania wszystkich zapytań w danym przebiegu.

Tym razem skorzystajmy z narzędzia Intela – [VTune](https://software.intel.com/en-us/vtune).

<div class="wp-container-63a097bf657a2 wp-block-group"><div class="wp-block-group__inner-container"><figure class="wp-block-table">| Aby skorzystać w pełni z możliwości VTune zainstaluj specjalny sterownik *[sampling driver](https://software.intel.com/en-us/vtune-help-sep-driver)* dający możliwość próbkowania zdarzeń sprzętowych. Instrukcja jak to zrobić [tutaj](https://software.intel.com/en-us/vtune-help-building-and-installing-the-sampling-drivers-for-linux-targets), sterownik (źródła) [tutaj](https://software.intel.com/sites/default/files/managed/02/d2/sepdk.tar.gz). |
|---|

<figcaption>Wskazówka</figcaption></figure></div></div>W pierwszej kolejności zobaczmy jak nasz testowy program wykorzystuje CPU:

<figure class="wp-block-image size-large">![](https://i0.wp.com/rrowniak.com/wp-content/uploads/2020/01/image.png?fit=840%2C499)</figure>Od razu widać, że wykorzystanie procesora jest bardzo nieoptymalne. Brązowe słupki oznaczają wykonywanie naszego programu. Przerwy mogą oznaczać czekanie na np. zasoby, operację IO lub synchronizację. Najbardziej będzie nas interesował główny wątek programu ponieważ to on determinuje czas trwania eksperymentu. Inny widok pokazuje schemat użycia CPU przez główny wątek:

<figure class="wp-block-image size-large">![](https://i1.wp.com/rrowniak.com/wp-content/uploads/2020/01/image-1.png?fit=840%2C158)</figure>Widzimy pewne sekwencje, które mogą oznaczać tworzenie wątków a potem czekanie na wyniki i tak kilka (set) razy. Te dłuższe przerwy to dokładnie 1s. A to oznacza, że w tym momencie przetwarzamy zapytanie odpalające `std::this_thread::sleep_for(1s)` (nasza symulacja operacji IO). Mieliśmy szczęście i mogliśmy zauważyć ten schemat. W realnym świecie już nie jest tak łatwo. Zatem mamy pierwszy problem – nasz algorytm jest nieoptymalny ponieważ przetwarzamy zapytania w „*paczkach*” (*batches*). To oznacza, że długość przetwarzania paczki będzie się równać najbardziej kosztownemu zapytaniu. A w tym czasie moglibyśmy zająć się kolejnymi zapytaniami.

Mamy poważny problem. A czy jest coś jeszcze? Tak, trzeba tylko spojrzeć czym CPU się zajmuje podczas wykonywania naszego eksperymentu:

<div class="wp-block-image is-style-default"><figure class="alignleft size-large is-resized">![](https://i1.wp.com/rrowniak.com/wp-content/uploads/2020/01/vtune-screenshot-1.jpg?fit=840%2C483)</figure></div>Powyższy zrzut ekranu pokazuje, że mamy dwa dominujące obszary. Pierwszy to główna funkcja `main` gdzie nasz program wykorzystuje 11.6% CPU.

Warto zatrzymać się tutaj na moment i zastanowić co oznacza ta metryka i jak ją interpretować. W uproszczeniu można powiedzieć, że profiler (np. VTune, perf) mierzy ile czasu procesor poświęcił na wykonanie poszczególnych funkcji naszego procesu. Jednak statystyki te odnoszą się tylko do naszego procesu, tzn. jeśli np. scheduler kernela uśpi nasz wątek na jakiś czas to tego nie zobaczymy w powyższych statystykach – uśpiony wątek nie konsumuje CPU! Więc nie będziemy mogli stwierdzić czy wolno działający program to wina IO czy naszego kodu, a przynajmniej nie zobaczymy tego bezpośrednio. Ten temat jeszcze poruszymy w dalszych częściach cyklu. Druga sprawa to procenty. W przypadku aplikacji jednowątkowej sprawa jest intuicyjna. W przypadku aplikacji wielowątkowej 100% (Total) to sumaryczny czas użycia CPU przez wszystkie wątki, nawet jeśli były one wykonane na różnych rdzeniach w tym samym czasie.

Wróćmy więc to meritum – nasza główna funkcja `main` konsumuje 11.6% CPU z czego znaczna część, bo aż 8.6% przypada na tworzenie nowych wątków. Jest to fragment który z łatwością będziemy mogli usprawnić. Jednak trzeba przypomnieć, że procenty odnoszą się tylko do zużycia CPU a nie sumarycznego czasu wykonania.

Obszar, który dominuje najbardziej to funkcje `__clone` i `start_thread`. Są to nasze stworzone wątki i najciekawszą informacją jest wysoki *CPU Time: Self* funkcji` start_thread`. Może to oznaczać znaczny koszt własny tej funkcji co prowadzi do dużego kosztu uruchomienia nowego wątku.

Wniosek jest jasny – tworzenie nowych wątków za każdym razem jest bardzo kosztowne. Trzeba zmienić nasz algorytm eliminując dwa problemy:

- Przetwarzanie paczek. To zły pomysł ponieważ czekamy aż wszystkie zapytania zostaną przetworzone i dopiero potem startujemy z nową paczką zapytań. Jest to mocno nieafektywne wykorzystanie CPU. Rozwiązanie: kolejka zadań. Będziemy wtedy w sposób ciągły przetwarzać zapytania.
- Tworzenie nowego wątku dla każdego zapytania. Jest to operacja kosztowna. Rozwiązanie: pula wątków (thread pool). Tworzymy pewną liczbę wątków na początku naszego programu a potem każdy wątek będzie sobie pobierał zadanie z kolejki zadań.

Ja już mam taką poprawioną implementację więc sprawdźmy wyniki:

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: plain; title: ; notranslate" title="">
$ ./processing_pipeline 10
Running Experiment_4_thread_pool for 8 threads
Control result: 6.49994e+10
Total sleep: 18920 ms, # yield: 49800, # requests: 100000
Waited 3381.23 ms, avg 29575 trans/sec
```

</div>Wow! W końcu nasza wielowątkowość zadziałała. Czas skrócił się z ~24 sekund do ~3.4 sekundy. W tym eksperymencie stworzyliśmy dokładnie tyle wątków ile sugeruje `std::thread::hardware_concurrency()` funkcja (u mnie 8). Czyli tak jak starsi i mądrzejsi radzą – tyle wątków ile rdzeni sprzętowych. To kończy zmagania, można się rozejść…

A jednak nie… Okazuje się, że z kilku powodów jesteśmy jeszcze daleko od ideału. Ale o tym w następnej części – przeanalizujemy obecną implementację, pomierzymy i zobaczymy jak usprawnić, a jest jeszcze sporo do usprawniania.