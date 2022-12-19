---
id: 479
title: 'Historia informatyki cz.2: bit i para'
date: '2019-01-06T13:04:20+00:00'
author: 'Rafał Równiak'
layout: post
guid: 'http://rrowniak.com/?p=479'
permalink: /it-pl/historia-informatyki-cz-2-bit-i-para/
image: /wp-content/uploads/2019/01/taton-moise-474481-unsplash_small.jpg
categories:
    - IT
---

W poprzednim wpisie, czyli [Historia informatyki cz.1: wspiąć się na ramiona olbrzymów](http://rrowniak.com/bez-kategorii-pl/historia-informatyki-cz-1-wspiac-sie-na-ramiona-olbrzymow/) przyglądaliśmy się skromnym początkom informatyki. Ale już wtedy, czyli jakieś 250 lat temu, człowiek zdradzał tendencje do automatyzacji i zastępowaniu siebie samego maszynami. Zobaczmy jak historia potoczyła się dalej i co ma przemysł tkacki z tym wspólnego…

  
Przygodę będziemy kontynuować od poniższej maszyny, która powstała ponad dwieście lat temu, czyli dosłownie kilka dekad później niż automaty opisywane w poprzedniej odsłonie. I jest to zarazem doskonały moment aby w końcu wyjaśnić o co chodzi z tym przemysłem tkackim.

<figure class="wp-block-image">![](https://docs.google.com/drawings/d/sdMk3lov8C4d0nkXQUinOLA/image?w=452&h=654&rev=50&ac=1&parent=1VTsw4UMYzyEA-uOT9G4AT-Ps4KUx6IxlpaJAB-DDb1Y)</figure>Otóż przemysł tkacki jako pierwszy w historii otrzymał programowalną maszynę, krosno tkackie, które wykonywało program nagrany na tak zwanych kartach perforowanych (zdjęcie poniżej). Wynalazek ten powołał do życia w 1805 r. francuski wynalazca Joseph Jacquard. Maszyna ta była w stanie uzyskać praktycznie dowolny wzór na tkaninie, ograniczeniem była wyobraźnia twórcy i, co w tamtym okresie było czymś nieznanym, umiejętności programistyczne. Karty perforowane, odpowiednik dzisiejszego programu komputerowego, to zwykły podziurkowany papier. I właśnie otwór na papierze lub jego brak jest informacją interpretowaną przez maszynę, papier jest przesuwany i głowica czyta kolejne kombinacje otworów. Każda taka kombinacja powodowała wybór odpowiednich nici co w sumie dawało oczekiwany wzór na tkaninie. Kartę można zawsze wymienić na inną nie zmieniając niczego w samej maszynie.

Tutaj należy się zatrzymać na chwilę ponieważ powyższe rozważania na temat maszyny Jacquard’a mają kapitalne znaczenie dla zrozumienia działania dzisiejszych komputerów.

<figure class="wp-block-image">![](https://docs.google.com/drawings/d/sESxEJmqB0Pit4oD7WIC_dQ/image?w=602&h=560&rev=46&ac=1&parent=1VTsw4UMYzyEA-uOT9G4AT-Ps4KUx6IxlpaJAB-DDb1Y)</figure>Bardzo istotne jest poznanie zasady działania maszyny na poziomie koncepcyjnym. I tak, szeroka taśma papierowa jest złączona końcami tworząc coś w rodzaju gąsienicy napędzającej czołg. Jak już wspomnieliśmy, na tej szerokiej taśmie znajdują się otwory stanowiące instrukcję jaki zestaw nici wybrać w danym momencie. Należy zauważyć, że połączony koniec z początkiem tworzy zapętlenie co w konsekwencji będzie skutkować powtarzalnością naszego programu. A jaką rolę pełnią otwory? Mechanizm nie jest skomplikowany; w głowicy maszyny znajduje się szereg zaczepów. Jeśli zaczep trafi na otwór to wybiera odpowiedni kolor nici, w zależności od lokalizacji otworu, bądź ich kombinacji.

<div class="wp-block-image"><figure class="alignleft">![](https://i1.wp.com/rrowniak.com/wp-content/uploads/2019/01/220px-Morris_and_Co_Anemone_1876.jpg?resize=220%2C334)<figcaption>Tkanina żakardowa z 1876r</figcaption></figure></div>Widzimy, że nie ma tu żadnej magii ani mistycyzmu, nie dopatrujemy się inteligencji po urządzeniu, po prostu maszyna wykonująca zapisane rozkazy. Można zauważyć, że programista kart perforowanych musiał zachować dużą precyzję ponieważ nawet niewielka zmiana rozstawu otworów spowoduje błędne działanie. Również programista musi być bardzo konkretny i korzystać z ograniczonego zestawu instrukcji. Niby oczywista sprawa a jednak często zapominana w kontekście współczesnych komputerów. Karta perforowana to prekursor pamięci komputerowej a sama maszyna to odpowiednik procesora. Karta z otworami to odpowiednik programu komputerowego. Co prawda maszyna nie wykonuje żadnych obliczeń ale realizuje zaprogramowane zadania. Jest to przełomowe choć mało doceniane odkrycie, człowiek po raz pierwszy stworzył programowalną maszynę gdzie program mógł być wymieniany, modyfikowany, kopiowany. I to ponad dwieście lat temu. Warto tu nadmienić, że polski wynalazca Jan Szczepanik znacznie usprawnił wytwarzanie kart perforowanych poprzez wykorzystanie technik fotograficznych i elektryki.

Maszyna Jacquard’a wykonywała tylko jedną czynność, więc jej uniwersalność była mocno ograniczona. Pewien postęp w tym kierunku został dokonany przez angielskiego matematyka Charlesa Babbage’a, który w 1835 roku zaprojektował maszynę różnicową, swego rodzaju mechaniczny kalkulator do obliczeń. Niestety projekt był tak skomplikowany, że ów wynalazca nie był w stanie wykonać działającego prototypu. Udało się to stosunkowo niedawno bo w 1991 roku i rezultaty były zdumiewające. Urządzenie podawało wyniki z dokładnością do 31 cyfr czego nawet większość współczesnych kalkulatorów nie potrafi, chociaż nie wynika to z ograniczeń technologicznych ale bardziej z braku takiej potrzeby podczas codziennych obliczeń. Wracając do naszego maszyny różnicowej, znamiennym jest sam fakt, że udało się zaprojektować urządzenie wykonujące obliczenia matematyczne i to z dużą dokładnością. Charles Babbage nie poprzestał na maszynie różnicowej i w 1837 roku rozpoczął projektowanie maszyny analitycznej. Był to już pierwszy programowalny komputer ogólnego przeznaczenia, niestety skomplikowanie projektu nie pozwoliło na jego budowę, do tej pory nikt nie zdołał zrealizować tego projektu. Jednak koncepcje użyte w projekcie były przełomowe. Program był zapisany na kartach perforowanych, podobnie jak w przypadku maszyny Jacquard’a, ale mógł wykonywać pętle i instrukcje warunkowe. Ogólnie rzecz ujmując program mógł wykonywać skomplikowane obliczenia i w teorii wykonać dowolny algorytm. Ta ostatnia cecha ma swoją nazwę – mówimy, że taka maszyna jest kompletna w sensie Turinga (Turing-complete). Ale o tym w kolejnych wpisach. W każdym bądź razie możemy uznać za fakt, że w drugiej połowie XIX w. zostały opracowane teoretyczne mechanizmy działania komputera. Oczywiście były to maszyny mechaniczne, wolne, ciężkie, często zasilane silnikami parowymi i dosyć prymitywne jeśli porównać do współczesnych osiągnięć. Czyli wypisz wymaluj epoka wiktoriańska.

Dalsza historia to zaprzęgnięcie elektroniki do pracy, ulepszanie koncepcji i osiągnięcia na polu algorytmiki i architektury sprzętowej. I temu będziemy się przyglądać w następnych odsłonach.