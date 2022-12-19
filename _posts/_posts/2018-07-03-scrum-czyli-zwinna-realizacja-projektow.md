---
id: 312
title: 'SCRUM czyli zwinna realizacja projektów'
date: '2018-07-03T06:48:49+00:00'
author: 'Rafał Równiak'
layout: post
guid: 'http://rrowniak.com/?p=312'
permalink: /dobre-praktyki/scrum-czyli-zwinna-realizacja-projektow/
image: /wp-content/uploads/2018/05/rawpixel-small-unsplash.jpg
categories:
    - 'Dobre praktyki'
    - Management
tags:
    - agile
    - 'inżynieria oprogramowania'
    - IT
    - 'product owner'
    - 'project manager'
    - scrum
    - waterfall
---

Wpis ten otwiera serię artykułów traktujących o zarządzaniu projektami i organizacji zespołów projektowych. Obecnie jedną z najpopularniejszych metod realizacji projektów jest SCRUM i wokół niego wszystko będzie się kręcić. Podzielę się też swoimi doświadczeniami i opiszę różne punkty widzenia, jako że miałem przyjemność wcielić się chyba w każdą rolę jaką definiuje SCRUM, a także uczestniczyłem w projektach jako klasyczny PM.

O czym będziemy dyskutować? Teraz zajmiemy się podstawami SCRUM. W następnych częściach przyjdzie mi mówić o:

- *Pojedynek ideologii: agile (SCRUM) vs pięciolatka (waterfall, v-model)*. Porównamy modele „zwinne” z tymi klasycznymi. Zobaczymy jakie problem trapią jeden i drugi styl.
- *[Czy SCRUM to Złoty Graal](http://rrowniak.com/it/czy-scrum-to-zloty-graal-zarzadzania-projektami/)?* Tutaj zastanowimy się gdzie SCRUM się sprawdza, a gdzie nie. Jak to wykryć w pierwszych etapach? A jeśli się nie sprawdza to jakie są alternatywy?
- [*Implementacja SCRUM i zagrożenia*](http://rrowniak.com/it/implementacja-scrum-zagrozenia/). Jak wdrożyć SCRUM i jakie czyhają zagrożenia? Zastanowimy się nad pewnymi, często niewidocznymi dla niedoświadczonego oka, problemami które SCRUMa zamieniają w waterfall.
- *A gdzie project manager?* No właśnie, co się stało z project managerem i dlaczego tak mało o nim mówimy?

## Agile

Pisząc wprowadzenie do SCRUM naturalnie trzeba zacząć od pojęcia *agile*, które to tłumaczy się w tym kontekście jako *zwinność*. [Agile manifesto](http://agilemanifesto.org/), bo od tego manifestu narodził się ruch *agile*, to nie jedna konkretna metoda tworzenia oprogramowania, a raczej zbiór zasad i dobrych praktyk (jest ich dwanaście) jakimi należy się kierować podczas takich prac. Nie będę ich przytaczał tylko podam pewną esencję, tak aby nie przynudzać zbytnio:

- Produkt jest ważniejszy niż procesy i dokumentacja.
- Miarą sukcesu jest satysfakcja klienta.
- Współpracuj z klientem od samego początku, dostarczaj oprogramowanie często, tak aby mieć szybką informację zwrotną.
- Bądź gotowy na częste zmiany wymagań – oprogramowanie ewoluuje, klient zmienia zdanie, co nie powinno dziwić.
- Najlepsze rozwiązania powstają w zmotywowanych i samoorganizujących się zespołach.

Jak widzisz nie jest to gotowy przepis, a raczej pewien fundament na którym można zbudować konkretne metodyki. I tak się stało, powstało ich wiele: [Scrum](https://en.wikipedia.org/wiki/Scrum_(software_development)), [Kanban](https://en.wikipedia.org/wiki/Kanban_(development) "Kanban (development)"), [Extreme programming](https://en.wikipedia.org/wiki/Extreme_programming "Extreme programming"), a to tylko kilka z brzegu.

## Co to jest Scrum?

Aby odpowiedzieć na to pytanie warto wyjść z nieco innej strony. Załóżmy, że mamy do zrobienia pewną, nietrywialną rzecz, może to być budowa gotyckiej katedry, zrealizowanie połączenia kolejowego pomiędzy miastami oddzielonymi górami lub wysłanie człowieka na księżyc. Jak podejść do takich zagadnień? No w pierwszym kroku należy dobrze (a nawet bardzo dobrze) zrozumieć założenia projektowe, chcemy wiedzieć czym będziemy się zajmować i jakie są oczekiwania pomysłodawców i sponsorów. Kolejnym krokiem będzie rozłożenie danego zagadnienia na czynniki pierwsze i zaprojektowanie rozwiązania. Czyli powstaje plan i architektura. Mając to możemy przystąpić do realizacji, co prawdopodobnie będzie najdłuższym etapem naszych zmagań. Na koniec weryfikujemy czy nasze dzieło spełnia zakładane oczekiwania. Brzmi sensownie? I tak w rzeczywistości jest. Ten sposób realizacji projektów w inżynierii nazywany [waterfallem](https://en.wikipedia.org/wiki/Waterfall_model), jest bardzo naturalny i logiczny. Można by powiedzieć, że jest niejako wpisany w nasz kod DNA. Postępujemy tak już od tysiącleci z niemałymi sukcesami. Ale w IT sprawy się nieco skomplikowały. O tym co poszło nie tak będzie w kolejnym odcinku, a teraz skupmy się na alternatywnym podejściu, które redefiniuje klasyczny porządek.

Otóż SCRUM, podobnie jak cała rodzina metodyk agile, proponuje inne podejście. Już na wstępie zakładamy, że koszt dokładnego poznania zagadnienia *a priori* jest bardzo wysoki, o ile jest to w ogóle możliwe. Zatem przygotowanie dokładnego planu i detalicznej architektury przed rozpoczęciem prac jest nieefektywne więc należy skupić się raczej na pewnym fragmencie, najczęściej tym na którym klientowi zależy najbardziej i spróbować go zrealizować od początku do końca. Nasz projekt będzie powstawał w sposób przyrostowy, w każdej iteracji będziemy dodawać kolejny kawałek, oddawać go klientowi i oczekiwać jego informacji zwrotnej. Mógłbyś zaprotestować i powiedzieć, że przecież klasyczna inżynieria wykorzystuje ten wzorzec od setek lat bo na przykład podczas budowy domu też mamy do czynienia z przyrostami i iteracjami. Powstają fundamenty, potem mury, dach i tak dalej. Ale to co innego, ponieważ z funkcjonalnego punktu widzenia fundamenty nie mają żadnej wartości. Są elementem kluczowym dla konstrukcji ale nie pełnią żadnej użytecznej funkcji dla końcowego użytkownika. Gdyby przeszczepić SCRUM na grunt budownictwa to wyglądało by to mniej więcej tak: w pierwszej kolejności budujemy dach aby deszcz nie padał na głowę, potem tworzymy łazienkę ponieważ to najważniejszy element, potem kuchnię, sypialnię, salon, itd. Do tego inwestor mógłby w trakcie prac zmienić kolejność realizacji prac bo na przykład sypialnia jest ważniejsza od kuchni… W budownictwie to nie zadziała ale IT to co innego. I jednym z najczęściej popełnianych błędów i źródeł złych wyobrażeń o IT jest analogia do budownictwa. To błędna analogia. Porozmawiajmy zatem o szczegółach.

## Role definiowane przez SCRUM

Jak chyba w każdej metodologii wytwarzania oprogramowania tak i w SCRUM definiujemy role. Są trzy podstawowe, tworzą one tzw. *core team*:

- *Product owner*, rola często mylona z project managerem. To nie to samo. Product owner nie jest bezpośrednio zaangażowany w tworzenie oprogramowania natomiast jest odpowiedzialny za priorytety zadań (*stories*), kontakt z klientem, tworzenie i utrzymywanie tzw. *backlogu* czyli mówiąc krótko – listy zadań (*stories, epics*) do zrobienia. Jest ekspertem domenowym i wyjaśnia wszystkie zawiłości wynikające z wymagań klienta zespołowi projektowemu. Reprezentuje klienta, jest niejako jego głosem w zespole projektowym. Product owner nie przydziela zadań konkretnym osobom, nie jest odpowiedzialny za organizację pracy zespołu, nie decyduje o architekturze rozwiązania ani o użytych technologiach (chyba, że klient ma sprecyzowane wymagania w tej kwestii).
- *Scrum master*, najczęściej ktoś z development team’u, organizuje pracę zespołu, dba o to aby cały ceremoniał wynikający wprost ze SCRUMa (np. *daily scrum, standup*) był przestrzegany, usuwa przeszkody jakie zespół napotyka realizując swoje zadania. Nie jest „wyżej” w hierarchii, nie przydziela zadań. Bardzo często rola scrum mastera łączona jest z rolą team lub tech lead’a.
- *Development team* to zespół programistów, testerów, projektantów itp. Czyli wszystkich tych którzy będą aktywnie uczestniczyć w tworzeniu rozwiązania. Do tej grupy również należy również scrum master. Zespół jest samoorganizujący, sam decyduje kto będzie pracował nad danym zadaniem, sam dobiera technologię tak aby czuć się komfortowo i być w stanie dostarczyć rozwiązanie o maksymalnej jakości.

Są jeszcze inne role (np. stakeholder) ale nie są kluczowe do zrozumienia o co chodzi w SCRUM.

## Proces

Wiemy już kogo potrzebujemy. Teraz zobaczymy jak to wszystko działa. Cały proces najlepiej opisuje poniższy rysunek:

<figure aria-describedby="caption-attachment-333" class="wp-caption alignnone" id="attachment_333" style="width: 959px">[![](https://i0.wp.com/rrowniak.com/wp-content/uploads/2018/06/Scrum_Framework.png?resize=696%2C388)](https://i0.wp.com/rrowniak.com/wp-content/uploads/2018/06/Scrum_Framework.png)<figcaption class="wp-caption-text" id="caption-attachment-333">https://en.wikipedia.org/wiki/File:Scrum\_Framework.png</figcaption></figure>

Na samym początku product owner opracowuje listę rzeczy do zrobienia (PBI – *product backlog item*). Oczywiście zgodnie z oczekiwaniami klienta. Początkowo są to bardziej obszary funkcjonalne aniżeli konkretne zadania. Gdybyśmy sobie wyobrazili tworzenie sklepu internetowego (abstrahując od tego, że istnieje mnóstwo gotowych rozwiązań) to moglibyśmy utworzyć kilka takich zagadnień: baza produktów, rozliczenia finansowe, raporty. Zauważ, że jest to opis funkcjonalny i domenowy ,a nie techniczny. Technologia jest przedmiotem, a nie podmiotem. Często zagadnienia te nazywamy epikami (*epics*).

Potem przychodzi czas na szczegóły. Pracę rozpoczyna cały zespół, a product owner jest tutaj centralną postacią. Tworzone są (nadal w backlogu) *stories* lub po prostu storyjki (brzmi dziwnie i można się oburzać ale takie spolszczenia w IT są normalne). Są to konkretne funkcjonalności przypisane do epików. Przykładem mogło by być „*jako użytkownik sklepu internetowego chciałbym przeglądać listę dostępnych produktów*” lub „*jako administrator sklepu internetowego chciałbym dodawać nowe produkty*„. Taka konwencja nazewnicza jest samo opisująca się i dobrze odzwierciedla o co chodzi. Mając listę storyjek w backlogu product owner definiuje priorytety a zespół deweloperski estymuje koszt (czas) potrzebny na wykonanie danej storyjki. Oczywiście zespół skupia się głównie na tych o najwyższym priorytecie. Nie spalamy czasu na mniej istotne fragmenty którymi i tak nie będziemy się zajmować w najbliższym czasie. Aby dokonać miarodajnej estymacji storyjek należy je rozbić na konkretne zadania (*tasks*).

Powyższe czynności odbywają się w sposób ciągły i przez całe życie projektu. Wymagania będą się zmieniać, klient będzie zmieniał zdanie, coś dodawał, z czegoś rezygnował. Takie pielęgnowanie *product backlogu* nazywamy *backlog grooming*’iem. Jest to jedna z fundamentalnych różnic w stosunku do waterfall’a gdzie lista rzeczy do zrobienia jest zamknięta po fazie planowania a starsi i mądrzejsi opracowali architekturę rozwiązania.

Czyli wiemy (z grubsza) co ile zajmie i co jest najważniejsze. Więc przystępujemy do układania sprintu. Sprint to zdefiniowany przedział czasu (od tygodnia do miesiąca) kiedy to pracujemy nad konkretnie wybranymi zadaniami. Zadania są tak wybrane aby odpowiadały priorytetom i mieściły się w sprincie co wynika z wcześniejszych estymacji. Powstaje tzw. *sprint backlog*. Product owner zatwierdza taki sprint i zespół może startować.

Codziennie odbywa się krótkie spotkanie, z reguły ok 15 min. Jest to słynny *daily scrum* lub *standup*. Każdy członek development team w żołnierskich słowach odpowiada na trzy pytania:

- co udało mi się zrealizować od ostatniego standup’u,
- co planuję zrobić w najbliższym czasie,
- czy wystąpiły jakieś nieoczekiwane problemy.

W spotkaniu uczestniczy również product owner, jednak nie wydaje on żadnych poleceń ani nie decyduje o sposobie prowadzenia prac projektowych. Próby „aktywnego” monitorowania i mikro-zarządzania są bardzo szkodliwe i przynoszą efekt ***zawsze*** odwrotny do zamierzonego – to bardzo częsty problem. Ale o tym w kolejnych odsłonach. Sprint zatwierdzony nie może być modyfikowany (oprócz wyjątkowych okoliczności – zdrowy rozsądek przewodnikiem).

Kiedy sprint zostanie zakończony product owner dokonuje przeglądu (*sprint review*) i odbiera zadania (storyjki). Zadanie jest odebrane wtedy kiedy spełnia wszystkie z góry określone warunki (*defninition of done*). Jest to wtedy tzw. wartość dodana do projektu i coś z czym klient powinien się zapoznać i podzielić swoją opinią. W tym samym czasie odbywa się tzw. retrospekcja – zespół projektowy przygląda się zamkniętemu sprintowi i zastanawia się co poszło zgodnie z planem, co nie zakończyło się druzgocącym sukcesem, co można usprawnić.

Cykl się zamyka i tworzony jest kolejny sprint na tych samych zasadach jak poprzedni. I to w zasadzie najważniejsze aspekty SCRUM. Oczywiście jest to tylko dosyć pobieżny przegląd ale daje dobry obraz tej metodologii.

Warto również wspomnieć że SCRUM to tzw. framework, czyli zestaw reguł i praktyk do wzięcia i implementacji, jednak nie są one ze sobą nierozerwalnie powiązane. Czyli możemy wziąć kilka elementów bez potrzeby implementacji całego SCRUM.

## Konsekwencje

Nie trzeba długo się zastanawiać, żeby zauważyć, że gotowość na zmiany w SCRUM jest bardzo wysoka. Mamy krótkie iteracje, możemy korygować kierunek rozwoju akcji. Bardzo szybko dostajemy informację zwrotną od klienta co jest być wielce pożądane. Bo na przykład jeśli nasze ostatnie zmiany nie odpowiadają klientowi to do „powtórki” jest tylko jeden sprint. Nie trudno się domyślić co się dzieje w przypadku wartefall…

Również widać, że planowanie jest mocno zredukowane, co nie oznacza, że ono nie istnieje. Ale trudno nie zgodzić się z tym, że szczegółowe planowanie i budowanie detalicznej architektury na początkowym etapie projektu gdzie nasza wiedza jest ograniczona nie będzie zbyt pomocne, żeby nie powiedzieć że to strata czasu. To również ma nieco bardziej subtelne implikacje nad którymi warto się zatrzymać na moment. SCRUM (i ogólnie *agile*) zakłada, że kluczowe decyzje projektowe i architektoniczne będą podejmowane wtedy gdy nasza wiedza jest dostateczna i poparta pewną praktyką. Jest to bardzo często niedoceniany element wynikający z czynnika ludzkiego (któż lubi się przyznawać do niedostatecznej wiedzy?).

I tu płynnie przechodzimy do kolejnej implikacji czyli redukcji perfekcjonizmu. Po prostu na perfekcjonizm i przeprojektowanie ([overengineering](https://en.wikipedia.org/wiki/Overengineering)) nie ma tu ani miejsca ani czasu. A perfekcjonizm (jako cecha charakteru, nie mylić z dobrym warsztatem, wiedzą i doświadczeniem, bo to diametralnie różne rzeczy) to bardzo groźny problem odbijający się niesłychanie negatywnie na efektywności zespołu i samej atmosferze. Jest to wróg zdrowego rozsądku. Zdania są podzielone co jest gorsze, czy perfekcjonizm czy braki warsztatowe w połączeniu z niechlujstwem.

Kolejnym, bardzo ważnym atutem SCRUM jest skupienie się na produkcie a nie planach i założeniach, które i tak wcześniej czy później stracą na aktualności i pójdą do kosza.

A więc czy SCRUM to złoty gral IT? Zastanowimy się nad tym w kolejnych odsłonach.