---
id: 491
title: 'Historia informatyki cz.3: początki rewolucji'
date: '2019-01-19T12:04:02+00:00'
author: 'Rafał Równiak'
layout: post
guid: 'http://rrowniak.com/?p=491'
permalink: /it-pl/historia-informatyki-cz-3-poczatki-rewolucji/
image: /wp-content/uploads/2019/01/fantasy-3208206_1280-1200x733.jpg
categories:
    - IT
tags:
    - 'historia informatyki'
    - 'lampy elektronowe'
    - 'system binarny'
    - 'system dwojkowy'
---

Już w 18 wieku wiedziano, że budowa uniwersalnej maszyny programowalnej jest możliwa. Ba, nawet powstały takie projekty. Niestety ich stopień skomplikowania nie pozwalał na realizację w tamtych czasach, a niektórych z nich nie udało się zbudować do dnia dzisiejszego. Czegoś jeszcze brakowało… Sprawdźmy co pozostało do odkrycia.

W pierwszej części artykułu [Historia informatyki cz.1 wspiąć się na ramiona olbrzymów](http://rrowniak.com/bez-kategorii-pl/historia-informatyki-cz-1-wspiac-sie-na-ramiona-olbrzymow/) przyglądaliśmy się skromnym początkom informatyki. Potem w drugiej części [Historii informatyki: bit i para](http://rrowniak.com/bez-kategorii-pl/historia-informatyki-cz-2-bit-i-para/) widzieliśmy jak cała sprawa zaczyna nabierać rozpędu. Dzisiaj prześledzimy kolejne odkrycia, które pozwoliły uwolnić się z kajdan mechaniki.

Ówczesne projekty maszyn programowalnych bazowały na konstruktach mechanicznych. Ich stopień skomplikowania rósł wykładniczo i nie było sposobu aby jakoś nad tym zapanować lub przynajmniej mieć jakąś kontrolę nad chaosem trybów i krzywek. Innymi słowy, pojawiła się granica, której przekroczenie wydawało się niemożliwe. Potrzebny był nowy przełom. I się pojawił.

W 1904 roku wynaleziono lampę elektronową. Jest to już nieco zapomniany element ale to właśnie on zapoczątkował rozwój elektroniki. Przed tym wynalazkiem prąd elektryczny był traktowany, podobnie jak węgiel, jako kolejna forma energii, owszem miał swoje poważniejsze zastosowania (np. telegraf, oświetlenie) ale natura tego nowego fenomenu była słabo poznana i często zaskakująca. To mocno ograniczało możliwości wykorzystania elektryki.

<div class="wp-block-image"><figure class="alignleft">![](https://upload.wikimedia.org/wikipedia/commons/5/58/6P1P.jpg)<figcaption>Lampa elektronowa</figcaption></figure></div>Wynalezienie lampy elektronowej całkowicie zmieniło ten stan rzeczy. A co to w ogóle jest ta lampa elektronowa? Jest to bańka szklana wypełniona gazem szlachetnym z różnymi elektrodami w środku. Jedną z fundamentalnych własności tego urządzenia jest możliwość wzmacniania sygnałów elektrycznych. W dużym uproszczeniu: słaby sygnał podany na wejściu zostaje przetworzony na sygnał większej mocy. Łatwo sobie wyobrazić użyteczność lamp elektronowych kiedy pomyślimy o takich urządzeniach jak wzmacniacze audio, wzmacniacze sygnałów telegraficznych albo nadajniki stacji radiowych. Zapytasz: dobrze ale co to ma wspólnego z maszynami programowanymi?

Otóż oprócz własności wzmacniających, lampy umożliwiają w prosty sposób tworzenie podstawowych cegiełek świata cyfrowego jakimi są [bramki logiczne](https://pl.wikipedia.org/wiki/Bramka_logiczna). Ale aby to zrozumieć należy się cofnąć aż do roku 1705, czyli aż ponad trzysta lat. Wtedy to jeden z największych gigantów matematyki, geniusz wszech czasów, czyli nie kto inny jak [Gottfried Wilhelm Leibniz](https://pl.wikipedia.org/wiki/Gottfried_Wilhelm_Leibniz) wynalazł system dwójkowy, a w każdym bądź razie wtedy upublicznił swoje odkrycie.

<div class="wp-block-image"><figure class="alignleft">![Gottfried Wilhelm Leibniz, Bernhard Christoph Francke.jpg](https://upload.wikimedia.org/wikipedia/commons/thumb/c/ce/Gottfried_Wilhelm_Leibniz%2C_Bernhard_Christoph_Francke.jpg/220px-Gottfried_Wilhelm_Leibniz%2C_Bernhard_Christoph_Francke.jpg)<figcaption>Gottfried Wilhelm Leibniz </figcaption></figure></div>Co więcej, ten genialny umysł pokazał, że system dwójkowy może być wykorzystany do syntezy zasad arytmetyki i logiki. Wyniki działań w systemie dwójkowym są równoważne do odpowiadających wyników w innych systemach liczbowych jak np. dziesiętnym. Czyli można konwertować liczby z jednego systemu do drugiego bez utraty ogólności. Leibniz jest też autorem innych, kapitalnych odkryć jak na przykład rachunek różniczkowy czy pojęcie całki jako sumy nieskończonej.

A dla czego system binarny? Ponieważ jest on dwustanowy (0 lub 1, fałsz lub prawda) przez co bardzo łatwo można go wykorzystać w systemach elektronicznych na zasadzie „jest sygnał” – „nie ma sygnału”. I wracając do naszych bramek logicznych – są to podstawowe operatory działań logicznych takie jak NOT, AND, OR, NAND, NOR, XOR, NXOR. Mając takie cegiełki możemy budować bardziej złożone konstrukty takie jak przerzutniki, rejestry, zatrzaski, sumatory, akumulatory.

Ludzkość uzbrojona w takie potężne narzędzia zaczęła konstruować pierwsze uniwersalne komputery programowalne. I wydawać by się mogło, że takie wynalazki powinny powstawać jak grzyby po deszczu. A jednak nie. Z kilku powodów. Po pierwsze wielu wynalazców nie doceniło lamp elektronowych i skupiali się na przekaźnikach jako elementach wykonawczych. Drugi problem to czasy w których przyszło konstruktorom żyć – dwie wojny światowe.

Dopiero w roku 1951 w Wielkiej Brytanii powstał w pełni programowalny komputer [Ferranti Mark 1](https://en.wikipedia.org/wiki/Ferranti_Mark_1), który umożliwiał skoki warunkowe – można było zaprogramować dowolny algorytm, innymi słowy maszyna była [zgodna w sensie Turinga](https://pl.wikipedia.org/wiki/Kompletno%C5%9B%C4%87_Turinga). Osiągi jak na dzisiejsze standardy nie były spektakularne, urządzenie było w stanie wykonać od 400 to 800 operacji na sekundę, w zależności od rodzaju operacji.

<figure class="wp-block-image">![](https://i1.wp.com/rrowniak.com/wp-content/uploads/2019/01/Ferranti-Mark-1-computer-with-some-of-the-many-cupboards-open-and-console-The-hooter.png?resize=696%2C472)<figcaption>Ferranti Mark 1</figcaption></figure>Program do tego komputera powstawał na kartach perforowanych, dokładnie ta sama technologia, którą wykorzystał Joseph Jacquard w roku 1805 konstruując swoje programowalne krosno – opisywałem to w [drugiej części](http://rrowniak.com/bez-kategorii-pl/historia-informatyki-cz-2-bit-i-para/).

I prawdopodobnie dzisiaj byśmy używali podobnych, zapewne nieco udoskonalonych maszyn gdyby nie pewne kolejne odkrycie… Ale o tym w następnym odcinku.