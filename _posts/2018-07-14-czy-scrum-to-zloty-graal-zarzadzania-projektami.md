---
id: 339
title: 'Czy SCRUM to Złoty Graal zarządzania projektami?'
date: '2018-07-14T20:10:02+00:00'
author: 'Rafał Równiak'
layout: post
guid: 'http://rrowniak.com/?p=339'
permalink: /dobre-praktyki/czy-scrum-to-zloty-graal-zarzadzania-projektami/
image: /wp-content/uploads/2018/07/Hammer.jpg
categories:
    - 'Dobre praktyki'
    - Management
tags:
    - agile
    - kanban
    - 'project management'
    - scrum
    - waterfall
    - 'zarzadzania projektami'
---

Oczywiście odpowiedź brzmi NIE, to nie jest Złoty Graal. Co więcej, istnieje spora grupa projektów gdzie nasza metodyka się nie sprawdzi. W tym artykule prześledzimy w jakich sytuacjach SCRUM nie będzie najlepszym wyborem i zobaczymy inne możliwości. Zastanowimy się jak ocenić czy SCRUM będzie pasował czy nie.

W [poprzedniej części](http://rrowniak.com/it/scrum-czyli-zwinna-realizacja-projektow/) pisałem o tym czym jest SCRUM i przedstawiłem pewne konsekwencje stosowania tej metodyki. W planach są następujące tematy:

- *Pojedynek ideologii: agile (SCRUM) vs pięciolatka (waterfall, v-model)*. Porównamy modele „zwinne” z tymi klasycznymi. Zobaczymy jakie problem trapią jeden i drugi styl.
- [*Implementacja SCRUM i zagrożenia*](http://rrowniak.com/it/implementacja-scrum-zagrozenia/). Jak wdrożyć SCRUM i jakie czyhają zagrożenia? Zastanowimy się nad pewnymi, często niewidocznymi dla niedoświadczonego oka, problemami które SCRUMa zamieniają w waterfall.
- *A gdzie project manager?* No właśnie, co się stało z project managerem i dlaczego tak mało o nim mówimy?

A teraz przejdźmy do meritum.

Przyglądając się naszej metodyce łatwo zauważyć, że opiera się ona na tak zwanym sprzężeniu zwrotnym, w tym przypadku będzie to [ujemne sprzężenie zwrotne](https://pl.wikipedia.org/wiki/Sprz%C4%99%C5%BCenie_zwrotne_ujemne) – „stabilizujące”. Jest to pojęcie często stosowane w inżynierii, w szczególności w elektronice. Chodzi o to, że w przypadku odstępstwa od zakładanej wartości następuje korekta. I w SCRUMie widać to bardzo dobrze, mamy krótkie iteracje w których dokonuje się przyrost projektowy. Jest on potem weryfikowany przez *product ownera* a następnie przez odbiorcę. Zespół dostaje informację zwrotną. To pozwala nam zaaplikować potrzebne korekty i poprawki. Takich cykli będzie bardzo dużo. I nie chodzi o owiane złą sławą „testowanie przez klienta”, a o nasze zrozumienie jego wymagań, oczekiwań i priorytetów. Jest jeszcze inny mechanizm korygujący nasz kurs, a mianowicie retrospekcja. Po każdym sprincie przeprowadzona jest retrospekcja. Podczas takiego spotkania każdy uczestnik wypowiada się o tym co poszło dobrze a co nie. Wynikiem takiego spotkania są akcje jakie należy wykonać celem poprawy procesu. SCRUM to nie przepis kucharski, a bardziej zestaw narzędzi, które należy dobrze dostroić i właśnie po to jest retrospekcja.

Warto zapamiętać ten fakt o sprzężeniu zwrotnym, ponieważ ma on kapitalne znaczenie dla wykorzystania potencjału tej metodologii. Jest to swego rodzaju kręgosłup, niestety bardzo często pomijany i niedoceniany. Mówiąc wprost SCRUM bez prawdziwego sprzężenia zwrotnego będzie raczej zabawą w SCRUMa aniżeli poważnym wykorzystaniem tej metodologii. Z mojego doświadczenia mogę powiedzieć, że to bardzo częsty błąd.

Innym czynnikiem degradującym jakość tej metodyki jest podatność na tak zwane „wrzutki”. Wrzutki to nic innego jak nieplanowane modyfikacje zakresu sprintu, najczęściej powstające poprzez wrzucanie innych rzeczy mających nagle wyższy priorytet. O ile zjawiska tego raczej nie da się uniknąć to częste zaburzanie zaplanowanych prac wprowadza chaos i powoduje wybicie zespołu z rytmu. Może to oznaczać poważne problemy wynikające z niewłaściwej priorytetyzacji zadań lub po prostu charakter projektu wymaga innej metodyki, lepiej dostosowanej do takich sytuacji jak np. Kanban. Wato dodać, że częste wrzutki powodują nieplanowane przełączanie się pomiędzy zadaniami (*context switching*), pochłania to czas i powoduje spadek efektywności zespołu (*velocity*). Jest to fakt, który niemal zawsze wywołuje nieprawdopodobne zdziwienie w wyższych kadrach zarządzających.

Kolejnym założeniem, które wszędzie jest prawdziwe, ale w SCRUMie najbardziej widoczne, to dojrzały i doświadczony zespół wykorzystujący dobre praktyki takie jak przeglądy kodu, testy jednostkowe i automatyczne, continuous integration, TDD, KISS, standardy kodowania. Zespół taki będzie w stanie wykorzystać cały potencjał SCRUMa i umiejętnie dostroi go do panujących realiów.

Nie wspominam o innych problemach jak choćby czynniki ludzkie (np. bardzo popularny kompleks Napoleona), ponieważ w równym stopniu dotyczą one innych metodyk.

### Podział typów projektów

Aby odpowiedzieć na pytanie „*czy SCRUM będzie działał?*” trzeba się zastanowić jaki projekt będziemy realizować. Istnieje kilka kategorii projektów informatycznych. Oczywiście to nie jest sztywny podział i bardzo rzadko mamy do czynienia z projektem, który pasuje tylko do jednej kategorii. Jednak kategoryzacja pozwoli nam się zorientować gdzie SCRUM się sprawdzi, a gdzie raczej szukać czegoś innego.

##### Projekty trudne technicznie i domenowo

To projekt, w którym jest więcej niewiadomych niż wiadomych. Będzie bardzo dużo aktywności polegających na eksplorowaniu nieznanych obszarów i testowaniu nowych technologii ([proof of concept](https://en.wikipedia.org/wiki/Proof_of_concept), proof of value, [spike](https://en.wikipedia.org/wiki/Spike_(software_development))). Wymagany jest wysoki stopień innowacyjności i myślenia nieszablonowego. Potrzebne jest odpowiednie środowisko pracy, które będzie pozwalać na częste wykonywanie eksperymentów, eksplorowanie różnych możliwości, analizowanie wyników i szybką adaptację na podstawie uzyskanych rezultatów.

Wyraźnie widać, że takie projekty powinny mieć charakter iteracyjny i kluczowym czynnikiem będzie możliwość reakcji na uzyskane rezultaty z eksperymentów. SCRUM bardzo dobrze wpisuje się w ten scenariusz.

##### Projekty o wysokim stopniu komplikacji domeny

W odróżnieniu od pierwszego typu ta kategoria zawiera te projekty, które są złożone pod względem domeny, ale występuje tam relatywnie mało czynników wymagających dodatkowych badań i eksperymentów. Wiedza jest skupiona wokół ekspertów domenowych, często ludzi, którzy uczestniczyli już w podobnych projektach. Domena jest raczej stała ale złożona, zmiany w wymaganiach bądź architekturze nie będą się pojawiały. Nierzadko takie projekty rozpoczynają się od wygrania kontraktu.

SCRUM wpisze się w ten scenariusz ale są inne metody, które będą równie dobrze się spisywać, a może nawet lepiej. Często w tych przypadkach stosuje się *waterfall* w różnych wariantach.

##### Projekty chaotyczne

Jest to typ projektów gdzie zmiany wymagań są bardzo częste, ciągłe, nieprzewidywalne i mają charakter imperatywny, to znaczy przychodzą z zewnątrz i są nienegocjowalne. Decyzje muszą być podejmowane natychmiastowo, ponieważ czas jest tutaj krytycznym czynnikiem. Sytuacje kryzysowe to chleb powszedni. Przykładem takich projektów mogą być rozwiązania w branży finansowej wykonujące automatyczne transakcje kupna i sprzedaży w czasie rzeczywistym. Tutaj czas to krytyczny zasób, warunki rynkowe zmieniają się bardzo szybko, a każdy poślizg lub błąd działania programu to straty sięgające milionów. Tego wolelibyśmy uniknąć, nawet za cenę naszej ulubionej metodyki.

SCRUM nie zadziała. Z całego bogactwa dobrodziejstw tej metodyki jedynie *standup* może mieć sens aby synchronizować pracę, ale inne aspekty nie przyniosą żadnych pożytków. Będą utrudniać pracę bądź nie zadziałają w najlepszym przypadku.

##### Projekty łatwe

Łatwa domena, brak większych trudności technicznych. Decyzje są jednoznaczne i niemal każdy może przewidzieć ich następstwa. Rozwiązania są oczywiste i bardzo łatwo stosować tak zwane dobre praktyki. Często są to powtarzalne projekty. Problem z takimi projektami jest taki, że nikt nie chce przyznać, że projekt nad którym pracuje jest *łatwy,* a prawdę mówiąc takich przypadków jest dużo. Kolejny problem jest taki, że dla jednych łatwy może być dla innych arcytrudną sprawą. Dużo zależy od doświadczenia zespołu. Pomińmy jednak kwestie relatywistyczne.

SCRUM może być z powodzeniem zaszczepiony w takim środowisku. Jednak są lepsze metody np. te oparte o ideę linii produkcyjnej ([assembly line](https://blog.antwerpmanagementschool.be/en/the-software-assembly-line)).

##### Projekty o charakterze *utrzymaniowym* (maintenance)

Domena znana, projekt o długiej historii. Jedyne rzeczy wymagające aktywnej pracy to naprawianie błędów (*bug fixing*) i dodawanie pomniejszych funkcjonalności (*client change request*).

SCRUM nie będzie tu najlepszym wyborem, choć przy dużym uporze może się sprawdzić. Bardziej odpowiednim modelem byłby np. Kanban.

##### Projekty typu bałagan

Dziki zachód, nie wiadomo co się dzieje, jednym słowem anarchia. Każdy interpretuje rzeczy po swojemu, realizuje je jeszcze inaczej. Kadra zarządzająca nie panuje nad sytuacją. Projekt rozwija się w kierunku nieustalonym, często jest to klasyczny przykład antywzorca [death march](https://en.wikipedia.org/wiki/Death_march_(project_management)).

Czy SCRUM pomoże? Nie, problem zapewne leży gdzie indziej. Próba zażegnania pożaru poprzez wprowadzenie SCRUMa to pomyłka i nieudolne odwracanie uwagi od sedna sprawy. Nie daj się na to nabrać. A najlepiej zadaj sobie pytanie co tu robisz.

## Słowo na koniec

Już chyba nie ma wątpliwości, że nasz tytułowy Graal nadal nie został odnaleziony. Ba, można odnieść wrażenie, że większość projektów wymaga innego traktowania. Więc jeśli masz decyzyjność i rozpoczynasz nowy projekt – nie zakładaj na ślepo żadnej metodyki tylko zrób analizę potencjalnych zysków i strat, czyli tradycyjnie zdrowy rozsądek.