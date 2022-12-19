---
id: 463
title: 'Historia informatyki cz.1: wspiąć się na ramiona olbrzymów'
date: '2018-12-30T17:30:46+00:00'
author: 'Rafał Równiak'
layout: post
guid: 'http://rrowniak.com/?p=463'
permalink: /it-pl/historia-informatyki-cz-1-wspiac-sie-na-ramiona-olbrzymow/
image: /wp-content/uploads/2018/12/Orion_aveugle_cherchant_le_soleil_small.jpg
categories:
    - IT
tags:
    - automat
    - automaton
    - historia
    - 'historia informatyki'
---

Tym wpisem chciałbym rozpocząć krótki cykl na temat historii informatyki. Wydawać by się mogło, że nie ma specjalnie o czym pisać, ponieważ większość rzeczy wydarzyła się w ostatnich latach, a rewolucja informatyczna to zasługa obecnych pokoleń. Nic bardziej mylnego. Zabiorę Cię w podróż poprzez ciekawe meandry historii, zobaczymy jakie wydarzenia miały wpływ na informatykę i w jakich czasach się wydarzyły.

Fundament informatyki to matematyka wyższa i teoretycznie nasza opowieść powinna się zacząć od przedstawienia odkryć i dokonań w tej materii. Problem w tym, że nie sposób wyjaśnić w kilku prostych słowach szeregu fundamentalnych odkryć matematycznych jakich dokonali tacy giganci jak choćby Euler, Hilbert, Gauss, Banach, Sierpiński, von Neuman, Turing. Odkryć, które pośrednio lub bezpośrednio miały wpływ na rewolucję informatyczną. To oczywiście tylko wierzchołek góry lodowej. Nawet jeśli byłbym w stanie podać doskonałe porównania, kapitalnie wyłożyć temat, to niestety skutek mógłby być odwrotny do zamierzonego. Nie byłby to ani porywający, ani ciekawy opis.

Z drugiej strony chciałbym zaznaczyć, że IT jakie dzisiaj znamy to wysiłek wielu tysięcy naukowców, wynalazców, matematyków, informatyków. I to na przestrzeni setek lat, a nie- jak można by zgadywać- kwestia ostatnich kilku dekad. Co bardziej zaskakujące, koncepty o znaczeniu fundamentalnym dla informatyki zostały wynalezione już wieku dziewiętnastym. Potem w wieku dwudziestym rozwój gwałtownie przyspieszył. Mam na myśli głównie algorytmikę i podwaliny dla współczesnych języków programowania i systemów operacyjnych. Ten fakt stoi w opozycji do popularnej opinii jakoby wszystko co najważniejsze dla przemysłu informatycznego powstało kilkanaście lat temu gdzieś w garażach małych kalifornijskich miasteczek. Wyobrażamy sobie młodych ekscentryków o genialnych predyspozycjach, którzy mając tylko chęć i umiejętności zmieniają świat, są motorem rewolucji społeczno-informatycznej. Ta romantyczna wizja to nic innego jak mit założycielski, który jest dosyć skutecznie promowany. Jak w każdym micie tak i tu jest ziarno prawdy, ale żeby odsiać plewy od ziarna musimy zagłębić się w historię branży.

Nie pozostaje nam nic innego jak wspiąć się na ramiona olbrzymów, aby zobaczyć więcej i dalej, pomijając w ciszy ich tytaniczne dokonania, jednak w żadnym wypadku nie umniejszając chwały.

Więc jak to się zaczęło? I co ma z tym wspólnego XIII i XIX wieczny przemysł tkacki a nie, na przykład, wynalazek Gutenberga? Przecież drukarka to jedno z podstawowych peryferiów komputera…

Zacznijmy od pierwszego wynalazku, który możemy nazwać pierwszym kalkulatorem. A mianowicie w roku 1623 genialny francuski matematyk Blaise Pascal zaprojektował i skonstruował urządzenie, które potrafiło dodawać i odejmować dwie liczby. Dodatkowo wykorzystując poprzednie działania kalkulator mógł mnożyć i dzielić liczby. Poniżej zdjęcie tego urządzenia.

<figure class="wp-block-image">![](https://i2.wp.com/rrowniak.com/wp-content/uploads/2018/12/Pascaline-CnAM_823-1-IMG_1506-black_small.jpg?resize=696%2C464)<figcaption>Kalkulator Pascala</figcaption></figure>Była to jedna z pierwszych maszyn liczących, jednak przełomowe wynalazki pojawiły się około sto lat później. Chodzi o *automaty*, urządzenia będące w stanie naśladować różne czynności ludzkie lub zwierzęce. Nie byłoby w nich nic nadzwyczajnego, ot takie drogie zabawki dla arystokratów, gdyby nie kilka szczegółów.

Jednym z przykładów tego gatunku jest *Pisarz* Pierre’a Jaquet-Droz’a. Arcydzieło to powstało około 250 (sic!) lat temu i jest przykładem geniuszu i precyzji ówczesnych inżynierów i zegarmistrzów.

<figure class="wp-block-image">![](https://i0.wp.com/rrowniak.com/wp-content/uploads/2018/12/boy-1.jpg?resize=696%2C612)<figcaption>*Pisarz* Pierre’a Jaquet-Droz’a</figcaption></figure> Chłopczyk na powyższej fotografii jest w stanie zapisać na kartce niemal dowolny tekst. Warto zobaczyć to urządzenie pracujące na żywo:

<figure class="wp-block-embed is-type-video is-provider-youtube wp-block-embed-youtube wp-embed-aspect-16-9 wp-has-aspect-ratio"><div class="wp-block-embed__wrapper"><iframe allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen="" frameborder="0" height="392" loading="lazy" src="https://www.youtube.com/embed/YAg66jrvpHA?feature=oembed" title="The Machines Taught To Recreate Life | Mechanical Marvels: Clockwork Dreams | Spark" width="696"></iframe></div></figure>Według wielu badaczy jest to pierwsza programowalna maszyna zachowana do dnia dzisiejszego, wiele z takich arcydzieł zaginęło w mrokach historii, być może niektóre z nich były jeszcze bardziej niesamowite.

Urządzenie to i jemu podobne wykorzystywały pamięć mechaniczną realizowaną za pomocy krzywek. Poniższa animacja przedstawia koncepcję.

<div class="wp-block-image"><figure class="alignleft">![](https://i2.wp.com/rrowniak.com/wp-content/uploads/2018/12/CamMechanism-small.gif?resize=256%2C492)</figure></div>Krzywka porusza się ze stałą prędkością kątową, a jej (często nieregularny) kształt zamieniany jest na ruch posuwisty popychacza, który wprawia w ruch inne mechanizmy. Kształt krzywki może być o wiele bardziej złożony co pomoże w realizacji bardziej złożonych operacji. I właśnie ta krzywizna jest swego rodzajem pamięcią mechaniczną.

Dzisiaj oczywiście informatycy nie frezują krzywek, aby zapisać różne sekwencje ruchów ale, co może dziwić, ta technologia jest używana do dnia dzisiejszego i nie widać żeby to miało się zmienić. Sam z tego korzystasz niemal codziennie… Niemal każdy silnik spalinowy wyposażony jest w takie krzywki, nazywane potocznie wałkiem rozrządu.

Wracając do naszych *automatów*, jest jeszcze inny wymiar tej technologii. W czasach swojej świetności urządzenia te dostępne były tylko dla najbogatszych. Arystokraci znajdowali przyjemność w obserwowaniu działania tych cudów mechaniki. Podchwycili to rewolucjoniści, porównali arystokratów do tych maszyn, twierdząc, że są dokładnie tacy jak *automaty*, wyglądają wybornie, zawsze elegancko ubrani, dbają o etykietę, potrafią pisać i grać na instrumentach, ale w środku jest pustka, nie ma duszy tylko mechanizm. A skoro tak, to przecież można zastąpić arystokratę maszyną. Idąc dalej, ich uprzywilejowana pozycja jest iluzją, a oni nie są więcej warci niż te maszyny. To twórca tych maszyn powinien cieszyć się większym uznaniem…

Dyskusja na temat zastąpienia maszynami człowieka, zapoczątkowana na dobre po tym jak człowiek stworzył działające maszyny wykonujące skomplikowane ludzkie czynności, nadal trwa i wywołuje kontrowersje mimo upływu niemal trzystu lat.

W następnym [wpisie](http://rrowniak.com/it-pl/historia-informatyki-cz-2-bit-i-para/) prześledzimy kolejne kroki milowe jakie człowiek zrobił przybliżając ludzkość do ery informatyki jaką znamy dzisiaj. Na przykład zobaczymy co ma z tym wspólnego maszyna tkacka…