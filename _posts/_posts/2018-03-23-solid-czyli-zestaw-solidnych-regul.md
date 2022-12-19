---
id: 182
title: 'SOLID czyli zestaw solidnych reguł'
date: '2018-03-23T15:12:12+00:00'
author: 'Rafał Równiak'
layout: post
guid: 'http://rrowniak.com/?p=182'
permalink: /dobre-praktyki/solid-czyli-zestaw-solidnych-regul/
image: /wp-content/uploads/2018/03/giammarco-boscaro-small-unsplash.jpg
categories:
    - 'Architektura oprogramowania'
    - 'Dobre praktyki'
    - 'Wzorce projektowe'
tags:
    - 'dependency inversion'
    - 'interface segregation'
    - 'inversion of control'
    - 'Liskov substitution'
    - 'open close'
    - 'single responsibility'
    - SOLID
---

Jednym z najbardziej rozpoznawalnych akronimów w inżynierii oprogramowania jest SOLID. Jednak po przeprowadzeniu setek rozmów rekrutacyjnych mogę stwierdzić, że z tą rozpoznawalnością bywa bardzo różnie. A szkoda, bo jest to zestaw reguł o dużym znaczeniu, warto więc wyjaśnić co to jest i dlaczego na rozmowach kwalifikacyjnych tak często pada pytanie o SOLID.

Powstało wiele opracowań na temat SOLID (możesz je bez problemu znaleźć w sieci) w odróżnieniu natomiast od znakomitej ich części my zastanowimy się czy można przedawkować SOLID i jakie będą tego efekty.

##### Czym jest SOLID i dlaczego o niego pytamy?

Pod nazwą SOLID kryje się pięć zasad związanych z inżynierią oprogramowania, w szczególności z programowaniem obiektowym. Jest to zlepek pierwszych liter pochodzących od nazw tych reguł. Są one uniwersalne i nie są przypisane do konkretnego języka programowania lub technologii, chociaż większość z nich odnosi się bezpośrednio do programowania obiektowego.

Na rozmowach rekrutacyjnych bardzo często pada pytanie o SOLID i nie chodzi o sprawdzenie wiedzy encyklopedycznej czy wyrywkową weryfikację znajomości formułek. To zagadnienie ma wymiar praktyczny. Po pierwsze jeśli znasz ten akronim, to z dużym prawdopodobieństwem żywo interesujesz się inżynierią oprogramowania, a w szczególności dobrymi praktykami, bo te reguły to zbiór właśnie takich praktyk. Punkt dla Ciebie! Kolejna ważna sprawa to dyskusja o poszczególnych zasadach. Tu możemy wymienić się spostrzeżeniami i sprawdzić jak dobrze czujesz się w roli inżyniera oprogramowania, jak rozumiesz dane prawidła. Dodatkowym plusem jest to, że temat ten jest dosyć luźny w przeciwieństwie do np. pytań natury algorytmicznej.

Jak już wspomniałem SOLID to zestaw dobrych praktyk i warto je mieć na uwadze podczas tworzenia oprogramowania. Jednak w skrajnych przypadkach mamy do czynienia z czymś w rodzaju religii. Istnieje grupa ludzi, która wyznaje te zasady w sposób dogmatyczny, a jak nietrudno zgadnąć każdy rodzaj fundamentalizmu jest szkodliwy. I ten przypadek nie jest wyjątkiem.

Przyjrzyjmy się więc tym zasadom.

##### Single responsibility

*Jedna odpowiedzialność* – tak byśmy mogli przetłumaczyć tę regułę na nasz rodzimy język. Chodzi o coś bardzo elementarnego, a mianowicie każdy fragment oprogramowania taki jak funkcja lub klasa powinien być odpowiedzialny tylko za jedną czynność. Jest to dosyć intuicyjna zasada w myśl powiedzenia, że jak coś jest od wszystkiego to jest do niczego. Więc jeśli projektujemy oprogramowanie, to powinniśmy wydzielić takie bloki funkcjonalne, które są skupione na konkretnych dobrze zdefiniowanych zadaniach, każdy blok to realizacja jednego zadania, każda klasa reprezentuje jeden spójny byt, każda funkcja implementuje dokładnie jedną czynność. Można również powiedzieć, że nie powinno być więcej niż jednego powodu do modyfikacji danej klasy lub funkcji.

Co dostajemy w nagrodę? Benefitów jest wiele. Jak choćby dobra struktura kodu, klarowność intencji programisty, prostszy kod, łatwość pisania i utrzymywania testów jednostkowych. Oczywiście do osiągnięcia tych precjozów sama zasada jednej odpowiedzialności nie wystarczy, ale z pewnością jest to krok w dobrym kierunku.

A teraz o przedawkowaniu. Cóż złego może się tu wydarzyć? Ano może i to dużo! Zasada ta doprowadzona do absurdu może skutkować bardzo poważnymi konsekwencjami takimi jak nieczytelny i zagmatwany kod, trudność w utrzymywaniu takiego dzieła. Dodatkowym skutkiem ubocznym jest mnożenie bytów ponad miarę. Jednym z najczęstszych przykładów takich nadużyć, co o zgrozo można często zobaczyć czytając wpisy ekspertów wyjaśniających właśnie tę zasadę, jest nadmierna komplikacja prostego problemu w imię tej zasady (i innych). Być może są to celowo przejaskrawione przykłady, aby pokazać sens reguły, ale problem w tym, że początkujący adept sztuki programowania może o tym nie wiedzieć. Tak więc prosty przykład składający się z kilku linijek kodu zamienia się w kilka lub kilkanaście klas, rozrasta się do kilku plików. Nie tędy droga!

##### Open-close

Mówiąc w skrócie, kod powinien być otwarty na rozszerzanie, a zamknięty na modyfikacje. A co to oznacza? Zacznijmy od końca, kod zamknięty na modyfikacje oznacza to, że jedynym powodem aby go modyfikować powinna być naprawa znalezionych błędów czyli bug-fixing. Dobra powiesz, a co jeśli klient chce wprowadzić zmiany samej funkcjonalności? Przecież musimy to jakoś zaimplementować czyli zmienić kod… Otóż niekoniecznie. I o tym mówi pierwsza część, czyli otwartość na rozszerzanie. Zatem nie modyfikujemy istniejących klas, a rozszerzamy je. Paradygmat programowania obiektowego dostarcza nam kilku narzędzi takich jak dziedziczenie lub kompozycja, które możemy wykorzystać do tego celu.

Zalety są mocnymi argumentami przemawiającymi za tą regułą, sprawdźmy więc co możemy zyskać.

- Nie modyfikujesz istniejącego kodu, więc nie musisz zmieniać powiązanych unit testów co bywa kosztowne i błędogenne. Rozjazd kodu z unit testami to chyba najczęstszy widok w starszych projektach.
- Podczas rozszerzania będziesz prawdopodobnie wykorzystywał istniejący i (miejmy nadzieję) przetestowany kod.
- Również ktoś może już korzystać z fragmentu, który normalnie byłby kandydatem do modyfikacji. Na szczęści nie mamy zamiaru tego robić, więc nie sprawimy niespodzianki w innym miejscu.

Wszystko pięknie, ale jak to wygląda w praktyce? Niestety, nieciekawie. Chyba wszystkie projekty, które wchodzą w fazę utrzymania (*maintenance*) stają się ofiarą notorycznego łamania tej reguły. Mógłbyś zapytać: ale jak to możliwe skoro to takie dobre prawidło? Wytłumaczenie jest bardzo proste. W projektach takich programiści często pracują pod presją czasową, zazwyczaj osoby decyzyjne preferują szybkie rozwiązania obarczone długiem technologicznym aniżeli rozwiązania solidne, ale bardziej czasochłonne. Niestety więc niesławny sposób zwany w branżowym żargonie „*quick-fix*” cieszy się sporą popularnością. Drugi powód to kod który jest (sic!) otwarty na modyfikację i zamknięty na rozszerzanie. I tutaj bez fundamentalnego refaktoringu się nie obejdzie. A na to mało kto się zgodzi. I tak koło się zamyka.

##### Liskov substitution

Jest to reguła związana bezpośrednio z polimorfizmem. Zwykle klasa bazowa jest początkiem bardziej złożonej hierarchii. Wiele klas może dziedziczyć z tej samej klasy bazowej. Często klasa bazowa stanowi interfejs, to znaczy nie musimy znać konkretnej implementacji tego interfejsu, ale opieramy się na tym interfejsie który niejako stanowi pewien kontrakt. Brzmi to dość dziwnie, ale jest to w gruncie rzeczy prosta zasada, którą można sparafrazować słowami „nie obchodzi mnie kto to zrobi i w jaki sposób, ma być zrobione”.

Wracając do sedna, zasada ta mówi, że zdefiniowany kontrakt nie powinien zostać semantycznie złamany. Czyli jeśli w pewnym fragmencie kodu korzystam z interfejsu to jakakolwiek implementacja tegoż interfejsu nie powinna skutkować nieoczekiwanym działaniem programu. Implementacja może realizować dany interfejs na różne sposoby, ale nie może wpłynąć negatywnie na aplikację która z niego korzysta. Czyli jeśli *podstawimy* lub zamienimy jedną implementację danego interfejsu inną implementacją tego samego interfejsu to program powinien zachować wszystkie niezmienniki (*invariants)*, czyli powinien się wykonać poprawnie.

##### Interface segregation

Interfejsy powinny być posegregowane w logicznie spójne fragmenty. Pod słowem interfejs należy rozumieć i te niskopoziomowe konstrukcje jak interfejsy na poziomie klas jak i te wysokopoziomowe jak np. WebServices. Zamiast jednego interfejsu zawierającego wszystkie metody i funkcje powinniśmy wprowadzić podział. Innymi słowy nie powinno dojść do sytuacji, w której część funkcji danego interfejsu jest nieużywana, ponieważ akurat tej funkcjonalności nie wykorzystujemy lub odwrotnie nie implementujemy danego fragmentu, ponieważ nie jest to nam potrzebne w konkretnym przypadku. Oznaczałoby to, że interfejs skupia zbyt dużo luźno powiązanych (lub wcale niepowiązanych) funkcjonalności.

Jednak przesadne rozdrobnienie powoduje nadmierną komplikację i paradoksalnie wprowadza chaos zamiast porządku. Wystarczy sobie wyobrazić osobny interfejs dla każdej metody. Widziałem już realizacje takich pomysłów i uwierzcie mi, nie jest to ani wygodne w używaniu, ani łatwe w utrzymaniu. A mówiąc wprost – koszmar!

##### Dependency inversion

Klasyczna topologia oprogramowania zakłada, że warstwy wyższego poziomu zależą od warstw niższego poziomu, a te znowu zależą od warstw jeszcze niższego poziomu i tak dalej. Brzmi logicznie i spora cześć oprogramowania właśnie tak funkcjonuje. Mamy więc drzewo zależności (a w praktyce jest to najczęściej graf). Oprogramowanie takie jest mocno spięte (*tightly coupled*), czyli zależności wszyte są w oprogramowanie, nie ma możliwości łatwej zmiany, a czasami taka możliwość byłaby bardzo pożądana, np. po to aby wyciągnąć dany fragment i przetestować go w izolacji lub użyć go w innej aplikacji, lub zastąpić go tymczasowo innym modułem.

Czy istnieje jakiś sposób, aby to osiągnąć? Istnieje. Ale trzeba przyjąć dwa założenia. Po pierwsze warstwy wyższego poziomu nie powinny zależeć od warstw niższego poziomu. A przynajmniej nie powinny zależeć w sposób bezpośredni. Wspólnym mianownikiem powinny być abstrakcyjne interfejsy. Wtedy warstwy nie muszą nic wiedzieć o sobie, ponieważ jedynym łącznikiem są interfejsy. Pewnie już domyślasz się dlaczego zasada *Liskov substitution* jest tutaj tak ważna. Drugie założenie mówi, że abstrakcyjne interfejsy nie powinny zależeć od implementacji, ale odwrotnie. To implementacja zależy od tych interfejsów, bo je implementuje.

Reguła ta niejako odwraca klasyczny sposób myślenia o zależnościach pomiędzy warstwami. Warstwy nie zależą od siebie, ale od abstrakcyjnych interfejsów.

Ale jest też ciemna strona tej reguły. Wyobraź sobie, że lądujesz w projekcie gdzie każda klasa posiada odpowiadający interfejs (osobny byt), widzisz mnóstwo tworów wyglądających mniej więcej tak: *ISomething*. Każda zależność pomiędzy klasami zrealizowana jest poprzez odpowiadający interfejs. Projekt taki staje się bardzo skomplikowany, kod jest bardzo złożony i zależności między klasami nie są już tak oczywiste. A cała rzecz polega na redukcji skomplikowania i wyrażania idei w sposób najprostszy. Znowu coś poszło nie tak. Oczywiście fanatyczni zwolennicy tej reguły będą jej bronić i będziesz słyszał wiele argumentów przekonywujących, że taki stan jest dobry i tak właśnie oprogramowanie powinno wyglądać. Ale nie daj się zwieść!

##### Podsumowanie

Zasady te są bardzo przydatne w programowaniu i powinny znaleźć się w skrzynce narzędziowej każdego programisty. Jednak podczas stosowania tej reguły należy korzystać ze zdrowego rozsądku, bo dogmatyczne stosownie się do tych prawideł może być równie szkodliwe co notoryczne łamanie tych reguł.

Niestety praktyka pokazuje, że z dużym prawdopodobieństwem będziesz miał (lub już masz) do czynienia z kodem, który w mniejszym lub większym stopniu łamie te reguły. Takie są realia i nie powinno to nikogo bulwersować, ponieważ napisanie kodu, który nie łamie żadnych reguł SOLID jest bardzo trudne, jeśli w ogóle możliwe. Co więcej, takie romantyczne myślenie jest utopią i może być znacznym problemem, ponieważ zawsze stoi w opozycji do zdrowego rozsądku. Tworzenie oprogramowania to zawsze jakiś kompromis, ktoś złośliwy mógłby powiedzieć, że ten kompromis to wybór pomiędzy dżumą a cholerą.