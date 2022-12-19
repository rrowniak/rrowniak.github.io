---
id: 536
title: 'Historia informatyki cz.4: viva la revolución czyli wolność, tranzystor i krzem'
date: '2019-02-02T15:35:19+00:00'
author: 'Rafał Równiak'
layout: post
guid: 'http://rrowniak.com/?p=536'
permalink: /it-pl/historia-informatyki-cz-4-viva-la-revolucion-czyli-wolnosc-tranzystor-i-krzem/
image: /wp-content/uploads/2019/02/carlos-irineu-da-costa-442504-small.jpg
categories:
    - IT
---

W poprzednich artykułach śledziliśmy stabilną ewolucję informatyki na przełomie setek lat. Rozwój tej młodej dziedziny przypominał inne dziedziny, jak choćby budownictwo, rolnictwo czy prawodawstwo, które potrzebowały nawet całych mileniów na rozwój. Gdyby elektronika i informatyka podzieliły ten los dzisiaj oglądalibyśmy nasze ulubione programy rozrywkowe na stylowych telewizorach lampowych, a komputery byłyby domeną akademików i dużych przedsiębiorstw. Jednak wiemy, że tak się nie stało…

W ostatnim [wpisie](http://rrowniak.com/bez-kategorii-pl/historia-informatyki-cz-3-poczatki-rewolucji/) na ten temat przedstawiłem przełomowe odkrycie jakim była lampa elektronowa. Jednak przemilczałem kilka problemów związanych z tym wynalazkiem. Lampy elektronowe były duże i z pewnych powodów bardzo trudne do miniaturyzacji. Ale nie jest to najgorszy problem. Lampa elektronowa działa na zasadzie kontrolowanej emisji elektronów, jednak aby taka emisja miała miejsce potrzebna jest odpowiednio wysoka temperatura jednej z jej elektrod (chodzi o katodę). Każda lampa ma wbudowaną *grzałkę* (fachowo mówiąc jest to obwód *żarzenia*), która pobiera sporo prądu. A w komputerach tych lamp było sporo, często liczba szła w tysiącach. Nie trudno wyobrazić sobie zużycie prądu. Ale nadal to nie wszystko. Lampy elektronowe „zużywały się”, tzn. ich parametry emisyjne pogarszały się z wiekiem. Można było określić stopień zużycia w procentach. Ktoś kiedyś, uwzględniając powyższe, wyliczył, że jeśli komputer PC klasy [486](https://pl.wikipedia.org/wiki/Intel_80486), czyli w dzisiejszych czasach zabytek i bezużyteczny złom, byłby zbudowany z lamp (teoretycznie możliwe ale niewykonalne) to co sekundę co najmniej jedna lampa ulegałaby uszkodzeniu. A zatem czego nam jeszcze brakuje w naszej układance?

<div class="wp-block-image"><figure class="alignleft">![William Shockley, Stanford University.jpg](https://upload.wikimedia.org/wikipedia/commons/f/f8/William_Shockley%2C_Stanford_University.jpg)<figcaption>William Bradford Shockley</figcaption></figure></div>Prawdziwą rewolucję zapoczątkowało odkrycie genialnego i jednocześnie kontrowersyjnego fizyka Williama Bradforda Shockley’a, za które został on uhonorowany nagrodą Nobla. On i jego zespół wynaleźli jako pierwsi tranzystor bipolarny, a był to rok 1949. Tranzystor jest absolutnym fundamentem naszej cywilizacji, wynalazkiem wszech czasów!. Bez koła moglibyśmy się obejść, bez tranzystora już nie.

  
Nawiasem mówiąc sława Shockley’a przyciągała wielu zdolnych inżynierów w okolice San Francisco. Każdy chciał pracować w jego zespole, ale nie każdy mógł otrzymać wymarzoną posadę. Nawet jeśli otrzymał to rzadko kiedy wytrzymał dłużej z tym naukowcem, ponieważ ów geniusz był, dyplomatycznie rzecz ujmując, nieco ekscentryczny. Efekt był taki, że inżynierowie ci zaczęli zakładać własne firmy o dziwnie znajomych nazwach jak na przykład Intel, Fairchild Semiconductor, Bell Telephone Laboratories czy Xerox PARC. I tak narodził się mit założycielski doliny krzemowej.

Wracając do naszego tranzystora, co to właściwie jest? To niepozorny element elektroniczny zbudowany z krzemu lub innego materiału zwanego półprzewodnikiem. Upraszczając sprawę, ma on podobne właściwości do

<div class="wp-block-image"><figure class="alignleft">![Znalezione obrazy dla zapytania transistor microscope](https://i0.wp.com/i.ytimg.com/vi/R6HF5mqdu-w/maxresdefault.jpg?w=696&ssl=1)<figcaption>Tranzystor pod mikroskopem</figcaption></figure></div>lampy elektronowej, czyli pozwala wzmacniać sygnały i być budulcem podstawowych cegiełek w cyfrowym uniwersum. Oczywiście jego właściwości są bardzo złożone, ale nie będę opisywał niuansów jego działania. Skupmy się na cechach odróżniających go od lamp elektronowych. Jest to struktura krzemowa nie zawierająca żadnych elementów mechanicznych, bardzo podatna na miniaturyzację. Tranzystor nie potrzebuje „dodatkowego” prądu i potrafi pracować z niskimi napięciami. Również nie zużywa się i wykazuje bardzo wysoką niezawodność. Zbyt pięknie aby było prawdziwe? Jest jeszcze piękniej.

Inżynierowie szybko zauważyli, że tranzystory można „pakować” na jednym kawałku krzemu (wafel krzemowy) w taki sposób, aby wykonywały one bardziej złożone zadania. I tak w roku 1958 Jack Kilby z firmy Texas Instruments stworzył pierwszy układ scalony (integrated circuit, IC).

<div class="wp-block-image"><figure class="alignleft is-resized">![](https://upload.wikimedia.org/wikipedia/en/thumb/4/42/Kilby_solid_circuit.jpg/220px-Kilby_solid_circuit.jpg)<figcaption>Pierwszy układ scalony</figcaption></figure></div>Kolejne odsłony różnych układów scalonych powstawały jak grzyby po deszczu. Jedne były mniej udane, inne bardziej. Ale trend był znany: mniejsze rozmiary, więcej tranzystorów, tańsze układy. Rozpoczęła się nowa era.

A prym w niej szybko zaczął wieść Intel. W roku 1971 firma ta wypuściła pierwszy 4-bitowy mikroprocesor 4004.

<div class="wp-block-image"><figure class="alignleft">![Intel 4004.jpg](https://upload.wikimedia.org/wikipedia/commons/thumb/5/52/Intel_4004.jpg/200px-Intel_4004.jpg)<figcaption>Intel 4004</figcaption></figure></div>Mikroprocesor ten umożliwiał wykonywanie programów, obsługiwał aż 64 instrukcji i był taktowany zegarem 740 kHz. W swojej wewnętrznej strukturze zawierał ok 2300 tranzystorów. Liczba ta przypomina ilość lamp elektronowych używanych w poprzednich komputerach. Jednak ten mikroprocesor mieścił się na palcu jednej ręki, nie wymagał elektrowni po sąsiedzku i był nieznacznie szybszy, czyli jakieś 1000 razy. Nie wspominając o jego możliwościach. Mówienie o ewolucji jest tu co najmniej nie na miejscu. Co więcej, Intel nie spoczął na laurach tylko zaczął bardzo regularnie wypuszczać coraz to potężniejsze mikroprocesory.

Naturalną konsekwencją tych odkryć było powstanie komputerów do użytku osobistego (personal computer, PC), które zaczęły gościć w coraz większej ilości domów. Był to znamienity czas, komputery i informatyka wymknęła się z laboratoriów firm technologicznych, z wojskowych baz, z sal uczelnianych i z korporacji. Już każdy mógł wziąć udział w tej przygodzie. I wziął, a to był katalizator napędzający już rozpoczętą rewolucję informatyczną

Ale to nie koniec historii, w następnych wpisach zobaczymy co się stało, kiedy pozwolono komputerom rozmawiać ze sobą…