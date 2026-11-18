---
id: 263
title: 'Microkernel &#8211; wzorzec architektoniczny'
date: '2018-05-01T07:30:43+00:00'
author: 'Rafał Równiak'
layout: post
guid: 'http://rrowniak.com/?p=263'
permalink: /dobre-praktyki/microkernel-wzorzec-architektoniczny/
image: /wp-content/uploads/2018/04/gears-cogs-machine-machinery-small.jpeg
categories:
    - 'Architektura oprogramowania'
    - 'Dobre praktyki'
    - 'Wzorce projektowe'
tags:
    - 'architektura oprogramowania'
    - Microkernel
    - 'Monolithic architecture'
---

Wzorce architektoniczne stanowią bardzo ważną część inżynierii oprogramowania. Są niejako instrukcją postępowania podczas rozwiązywania pewnych powtarzających się problemów. Dzisiaj weźmiemy na pulpit wzorzec architektoniczny, który jest związany głównie z (ale nie tylko) architekturą systemów operacyjnych – microkernel (nie mylić z kernelem systemu operacyjnego!). Podam ogólny zarys tego wzorca i zrobię krótką analizę uwzględniając różne kryteria. Ta ostania rzecz jest szczególnie **bardzo ważna** dla programistów i architektów oprogramowania – zobaczymy jakie należy przyjąć kryteria oceny i na co zwracać uwagę podczas analizy wzorców projektowych.

## Microkernel

Wzorzec ten definiuje strukturę oprogramowania np. systemu operacyjnego dzieląc ją na rdzeń czyli po angielsku *kernel* (nazywany również *mikrokenelem*) i stowarzyszone moduły. Poniższy rysunek przedstawia tą ideę.

[![](https://i2.wp.com/rrowniak.com/wp-content/uploads/2018/05/microkernel.jpg?resize=696%2C244)](https://i2.wp.com/rrowniak.com/wp-content/uploads/2018/05/microkernel.jpg)

Kernel zawiera implementację minimalnego zestawu funkcjonalności jaki jest potrzebny aby zrealizować bardziej złożone zadania. A realizacją tych złożonych zadań zajmą się stowarzyszone moduły. Brzmi dość mgliście, wiem. Spróbujmy znaleźć jakąś analogię aby mieć lepsze wyobrażenie na ten temat i nieco uzbroić intuicję.

Wyobraź sobie pralkę automatyczną. Zawiera ona kilka mechanizmów takich jak silnik napędowy, pompa wody, grzałka do podgrzewania wody, elektrozawory, filtry i kilka czujników. Producent mógłby Ci udostępnić zestaw wajch do sterowania każdą z tych części, powstał by trochę taki star-trek. I teoretycznie mógłbyś prać ubrania tak jak można to robić używając klasycznej pralki automatycznej. Ba, nie byłbyś ograniczony żadnymi programami. Ale wygląda na to, że świat poszedł w innym kierunku. Co nie oznacza, że nie ma tych mechanizmów w pralce i nie można nimi sterować. Można ale robi to kto inny. Więc taka „goła” pralka to odpowiednik kernela. Udostępnia ona minimalny zestaw narzędzi potrzebnych do wykonania danego zadania. Ale nic ponadto. Uważny obserwator zanotuje, że takie pralki nie podbiły rynku. Kontynuując naszą analogię, na scenę wkraczają wspomniane moduły. Rozszerzają one nasz kernel tak aby uczynić nasze życie łatwiejszym. I tak nasza pralka otrzyma zestaw programów, przyjazny panel sterowania, obsługę sytuacji wyjątkowych, funkcję robienia kawy i takie tam podobne. Widać więc, że moduły korzystają z funkcji udostępnionych przez kernel ale same nie operują bezpośrednio na sprzęcie ani nie są absolutnie konieczne do jego działania.

Mając pewne wyobrażenie na ten temat porozmawiajmy o detalach. Już wiemy, że kernel implementuje podstawowe funkcjonalności, które są udostępnione poprzez tzw. [API](https://pl.wikipedia.org/wiki/Interfejs_programowania_aplikacji) (application programming interface). API może przyjąć formę [web-service](https://pl.wikipedia.org/wiki/Us%C5%82uga_sieciowa), interfejsu [REST](https://pl.wikipedia.org/wiki/Representational_State_Transfer) lub [RPC](https://pl.wikipedia.org/wiki/Zdalne_wywo%C5%82anie_procedury) albo co ma najczęściej miejsce w przypadku systemów operacyjnych i [systemów wbudowanych](https://pl.wikipedia.org/wiki/System_wbudowany) (ang. *embedded*) – interfejsu [C](https://en.wikipedia.org/wiki/C_(programming_language)). Istnieją również moduły. Czasami można spotkać się z określeniem *services* lub *components*, co opracowanie to inna nomenklatura. W każdym bądź razie moduły korzystają z interfejsu jaki udostępnia kernel. I same udostępniają nowe interfejsy. Może to być rozszerzenie interfejsu kernela lub stworzenie nowego, definiującego wyższy poziom abstrakcji. Moduły mogą korzystać tylko z API kernela – wtedy mówimy o modułach wewnętrznych, internal modules. Ale jest też kategoria modułów, które mogą korzystać z API innych modułów (innych ale tylko tych *internal*) – wtedy mamy do czynienia z modułami zewnętrznymi, external modules.

## Mircokernel vs Monolithic

Bardzo często wzorzec microkernel jest porównywany do podejścia monolitycznego, czyli braku separacji na kernel i moduły. Mogło by się wydawać, że sprawa jest oczywista; mikrokernel wprowadza strukturę i pewne reguły więc będzie jakościowo lepszy. Teoria stoi za mikrokernelem. Ale tak nie jest. Dobitnym przykładem jest jądro Linux’a. Jest to monolityczna architektura, która się sprawdziła. Istnieje nawet zapis słynnej [dysputy](https://en.wikipedia.org/wiki/Tanenbaum%E2%80%93Torvalds_debate) po między twórcą jądra systemu Linux Linusem Torvald’em a znanym teoretykiem informatyki Andrew’em S. Tanenbaumem, którzy to prowadzili długą debatę nad wyższością jednego podejścia nad drugim.

## Zalety i wady

Zalety:

- zdefiniowana struktura
- możliwość łatwej wymiany modułów
- rozszerzalność
- możliwość implementacji tzw. modelu plug-in’owego
- możliwość dostosowania do potrzeb, nie używane moduły mogą być wyłączone

Wady:

- większa złożoność
- dodatkowe narzuty wydajnościowe, głownie chodzi o takie problemy jak [*cache misses*](https://en.wikipedia.org/wiki/CPU_cache#CACHE-MISS), *tlb misses*

## Analiza

#### Agility

Wysoki stopień adaptacji do metodyk zwinnych ponieważ podział strukturalny i zdefiniowany interfejs API pozwala na łatwą dystrybucję zadań pomiędzy zespołami. Implementacja może być przyrostowa i iteracyjna. Nowe funkcjonalności mogą być dodawane szybko. Jedynym krytycznym punktem jest API, każda zmiana ma ogromny wpływ na resztę komponentów.

#### **Ease of deployment**

Wdrażanie rozwiązań opartych o ten wzorzec jest łatwe, późniejsza aktualizacja polega na wymianie lub dodawaniu nowych modułów.

#### **Testability**

Testowalność jest bardzo ułatwiona. Każdy moduł może być testowany w izolacji ponieważ funkcjonalność kernela może być emulowana. Również kernel może być testowany osobno ponieważ udostępnia API, które będzie wykorzystane do testów.

#### **Performance**

Tutaj sprawa jest nieco bardziej skomplikowana. Z jednej strony nieużywane moduły mogą być wyłączone lub w ogóle nie zainstalowane. To spowoduje mniejsze zapotrzebowanie na zasoby co może przełożyć się na wydajność. Ale z drugiej strony mamy dodatkowy narzut w postaci API i sam podział strukturalny wymusza więcej kodu. A to może przełożyć się bezpośrednio na wydajność, chodzi głównie o [*cache misses*](https://en.wikipedia.org/wiki/CPU_cache#CACHE-MISS).

W praktyce rozwiązania oparte o ten wzorzec mogą charakteryzować się gorszymi wynikami. Jednak różnice mogą być niewielkie i tam gdzie wydajność nie jest najważniejszym czynnikiem wzorzec może być stosowany z powodzeniem.

#### **Scalability**

Skalowalność jest niska ponieważ mamy do czynienia z pojedynczymi jednostkami, które są dosyć mocno odizolowane. Wzorzec jest silnie scentralizowany.

#### **Ease of development**

Rozwój oprogramowania opartego o ten wzorzec jest stosunkowo łatwa. Podział narzucony przez wzorzec daje możliwość tworzenia modułów w izolacji, możemy je tworzyć niezależnie w oparciu o zdefiniowany interfejs. Dodatkowo kernel może być emulowany. Programistyczny raj…

Ale jest też ciemna strona tego zagadnienia. Wszystko działa jak wyżej opisałem pod warunkiem, że API jest stabilne i dobrze zaprojektowane. A to dość trudna sprawa. Do tego dochodzi wersjonowanie interfejsów. Kolejnym problematycznym fragmentem jest sam kernel. Wymaga on od programistów dużej wiedzy i dobrego warsztatu ponieważ jest on centralnym punktem systemu i problemy z nim związane będą się propagowały na cały system.

## Podsumowanie

To tyle jeśli chodzi o microkernel. Wiesz już co to za wzorzec, poznałeś jego silne i słabe strony. Dodatkowo zobaczyłeś jak wygląda analiza tego wzorca. Pamiętaj jednak aby w takich analizach uwzględniać czynniki specyficzne dla Twojej firmy, projektu, klienta itp. Ja tego nie zrobiłem, ponieważ nie mogłem poczynić założeń, które wychodziły by poza granice ogólności. W przyszłości będę powracał do tej tematyki i weźmiemy na pulpit kolejne wzorce.