---
id: 93
title: 'Bitcoin: mity i legendy wyznawców'
date: '2018-02-13T06:53:34+00:00'
author: 'Rafał Równiak'
layout: post
guid: 'http://rrowniak.com/?p=93'
permalink: /bitcoin/bitcoin-mity-i-legendy-wyznawcow/
categories:
    - Bitcoin
tags:
    - Bitcoin
    - blockchain
    - kryptowaluta
    - mity
---

[![](https://i1.wp.com/rrowniak.com/wp-content/uploads/2018/02/annette-fischer-498468_small.jpg?resize=627%2C343)](https://i1.wp.com/rrowniak.com/wp-content/uploads/2018/02/annette-fischer-498468_small.jpg)

Technologia Bitcoin, czyli wirtualna waluta jest dzisiaj odmieniana przez wszystkie przypadki. Budzi wiele emocji i jest przedmiotem wielu płomiennych dyskusji. Co więcej, nierzadko dochodzą do tego pieniądze, czasami bardzo duże pieniądze. To mieszanka wybuchowa, która przyczyniła się do powstania wielu zwalczających się frakcji. Chyba najłatwiej je podzielić na: obóz wyznawców wirtualnej waluty, obóz zdeklarowanych wrogów, a gdzieś pomiędzy znajdują się wszyscy inni. Jak nietrudno zgadnąć powstało mnóstwo mitów, propagowanych zarówno przez jedną jak i drugą stronę. Mity te znalazły bardzo podatny grunt, ponieważ zasada działania kryptowalut jest bardzo trudna do zrozumienia dla kogoś, kto nie zna podstaw kryptografii, systemów rozproszonych i matematyki wyższej. Czyli, nie oszukujmy się, zdecydowanej większości użytkowników internetu.

Będzie to cykl trzech wpisów, podzielony na mity wyznawców Bitcoina, [mity zagorzałych przeciwników](http://rrowniak.com/it/bitcoin-mity-i-legendy-wrogow/) i kilka interesujących faktów na koniec.

### Mity wyznawców Bitcoina

###### Mit 1: Istnieją drobne techniczne przeszkody, ale nie ma najmniejszego powodu do zmartwień.

*Zostaną one rozwiązane lada dzień…*

No cóż, mamy powody do zmartwień i to duże. Największy problem to skalowalność technologii stojącej za Bitcoinem ([scalability problem](https://en.wikipedia.org/wiki/Bitcoin_scalability_problem)), a właściwie to jej brak. W skrócie można to ująć w ten sposób, że liczba transakcji jakie mogą zostać przetworzone w danym okresie czasu jest stała i nie da się tego ograniczenia obejść bez gruntownej przebudowy całego mechanizmu. Sieć może przetworzyć od trzech do siedmiu transakcji na sekundę. Jest to liczba niezależna od ilości użytkowników. Są to bardzo liche wyniki, w szczególności jeśli waluta ma aspirację do bycia ogólnoświatową. Jest kilka propozycji na poprawę sytuacji, ale wymagają one zmiany dotychczasowych reguł, co jest bardzo trudne do wprowadzenia i powoduje powstawanie tzw. hard fork’ów. Jest to sytuacja gdzie następuje podział sieci użytkowników danej kryptowaluty na tych co korzystają z niej tak jak dotychczas, czyli po staremu i na tych co przyjmują nowe warunki i postępują według nich. Obie sieci nie są kompatybilne ze sobą.

Kolejny problem to liniowy przyrost rozmiaru rejestru transakcji ([blockchain](https://en.wikipedia.org/wiki/Blockchain)). W chwili pisania tego tekstu rejestr zajmuje ponad 150 GB przestrzeni dyskowej. Ktoś może powiedzieć, że to niewiele jak na dzisiejsze standardy, ale ten rozmiar ciągle rośnie i zaczyna być uciążliwy dla kogoś, kto chce być pełnoprawnym członkiem sieci Bitcoin (full node) – musi on bowiem ściągnąć całą bazę z sieci. Taki ciągły przyrost rejestru jest niejako wpisany w filozofię Bitcoina, więc to się nie zmieni. W chwili obecnej przyrost jest niewielki, ponieważ liczba transakcji na sekundę jest mała. Ale ze zwiększeniem przepustowości (patrz poprzedni problem) zwiększy się tempo przyrostu rejestru, co w skrajnych przypadkach może być dużym problemem.

###### Mit 2: Już niebawem Bitcoin zastąpi klasyczne waluty.

Optymiści mówią, że za kilka lat będziesz płacił tylko Bitcoinem. Tak się jednak nie stanie z kilku powodów. Po pierwsze: wykonanie transakcji jest powolne. W zależności od pewności jaką chcemy mieć czy dana transakcja została umieszczona w bloku, a potem ten blok nie został odrzucony, trzeba czekać od dziesięciu minut do godziny. System potrafi przetworzyć tylko kilka transakcji na sekundę (patrz Mit 1). To zdecydowanie za mało.

Kolejnym problemem, raczej nie do przejścia, jest brak kontroli nad emisją pieniądza wirtualnego. Wątpliwe jest aby obecni emitenci klasycznego pieniądza, czyli bardzo potężna siła, chcieli nagle zrezygnować z tego przywileju. Wojny wybuchały już z bardziej błahych powodów…

Inna sprawa to anonimowość, a raczej jej brak. Wydawać by się mogło, że jest całkowicie odwrotnie, że Bitcoin gwarantuje pełną anonimowość. Jednak ta kończy się kiedy Twój unikalny adres zostaje powiązany z Twoją osobą, wiadomo wtedy jakie transakcje wykonałeś, ile bitcoinów otrzymałeś, kiedy itp. Widać wszystko i to od samego początku. To tak jakbyś ujawnił historię swoich transakcji bankowych. Nie zapominaj, że rejestr wszystkich transakcji jest publicznie dostępny. A do takiej sytuacji może dojść w kuriozalnie łatwy sposób, wyobraź sobie, że jesz obiad z przyjacielem i on płaci za całość mówiąc: później się rozliczymy – przelej mi w bitcoinach na mój adres, zaraz Ci go prześlę… Wtedy Ty wiesz, że przesłany adres należy do kolegi, a kolega będzie znał Twój adres po zakończeniu transakcji. I może on prześledzić wszystkie transakcje z udziałem Twojego adresu. Oczywiście istnieją praktyki mające na celu ochronę przed takimi sytuacjami, jak na przykład przyjmowanie każdej płatności na inny adres (nie istnieje limit unikalnych adresów jakie możesz mieć) lub posiadanie wielu portfeli. Ale nawet takie praktyki nie gwarantują pełnej prywatności i im bardziej skomplikowana procedura, tym większe szanse na pomyłkę.

I jeszcze jedno. Dzisiaj kurs wymiany Bitcoina jest bardzo niestabilny. Jest to kolejny dyskwalifikujący czynnik, no chyba że ktoś lubi hazard. Od waluty oczekujemy stabilności i wymienialności na inne dobra. W chwili obecnej Bitcoin przyciąga ludzi bardziej w celach spekulacyjnych niż po to, aby pójść na kawę i zapłacić za nią wirtualną walutą.

O ile krytptowaluty to rewolucyjny pomysł, to jeszcze trochę musi minąć czasu, aby wszystkie problemy wieku dziecięcego zostały rozwiązane. Nie należy zapominać o przekonaniu całej rzeszy ludzi, którzy nie czują się pewnie w świecie kryptowalut, do tego nowego wynalazku. To oni będą siłą napędową, a nie grupa wielbicieli i pasjonatów.

###### Mit 3: Technologia blockchain to rewolucja na miarę Internetu, początek Internetu 2.0.

No cóż, można by streścić ten mit tak: minęło około dziesięć lat od pojawienia się tej technologii i nic. To znaczy nic oprócz kryptowalut. Nie widać na horyzoncie żadnego z zapowiadanych przełomów. Coś jest nie tak…

Pojawiło się mnóstwo teoretycznych pomysłów na zmianę obecnego świata, część z tych pomysłów doczekała się prototypów w postaci oprogramowania realizującego dane założenia, pompowano grube pieniądze w takie projekty, bo wierzono w nadchodzącą rewolucję. Niestety rzeczywistość szybko i brutalnie weryfikuje różne, czasami nawet słuszne i ciekawe pomysły. I zweryfikowała te oparte na technologii blockchain. W chwili obecnej nic rewolucyjnego nie powstało (nic oprócz kryptowalut), nic oprócz utopijnych wizji tech-proroków. Ale dlaczego? Co poszło nie tak?

Technologia blockchain to potężne narzędzie, można w uproszczeniu powiedzieć, że osiąga globalne zaufanie w oparciu o uczestników sieci, którym jednak nie możesz ufać z osobna. W przypadku kryptowalut ma to sens, nie ma centralnego organu, więc musisz ufać sieci. I to działa. Aby nie dopuścić do przejęcia sieci przez jeden organ, ta technologia wymaga relatywnie dużej liczby użytkowników. Jeśli połowa sieci będzie pod kontrolą jednej organizacji, to będzie mogła ona wpływać na reguły jakie zostały ustalone. Kolejna ważna własność technologii blockchain to bardzo duży wysiłek, graniczący z niemożliwością, potrzebny do wprowadzenia zmian już zapisanych. Bitcoin wykorzystuje do tego odmianę algorytmu [proof-of-work](https://en.wikipedia.org/wiki/Proof-of-work_system), który wymaga ogromnej mocy obliczeniowej.

Jak widzisz wszystko o czym piszę jest dosyć skomplikowane. I to też jest problem, bo jak przekonać statystycznego Kowalskiego, że powinien wspierać pomysły oparte na technologii blockchain?

Biorąc pod uwagę powyższe i obecne techniczne problemy opisywane w micie 1 widać, że nie jest to technologia rozwiązująca wszystkie problemy na świecie i w pewnych obszarach po prostu się nie sprawdza, bo nie jest do tego stworzona. Dla przykładu jednym z pomysłów są dowody osobiste oparte na rejestrze blockchain. Ale jak przekonać zwykłego zjadacza chleba, że powinien aktywnie wspierać tego typu inicjatywę? I jaki problem miałby być rozwiązany? Co zwykły człek będzie z tego miał? Zobaczmy inny przykład – dinozaury takie jak Visa i MasterCard już dawno powinny zniknąć z rynku na rzecz rozwiązania opartego na blockchain. Trudno znaleźć lepsze zastosowanie dla tej technologii. A jednak są nadal i mają się całkiem nieźle… No i tu dochodzimy do sedna problemu – jeśli jest coś, co działa to bardzo trudno będzie to coś zastąpić czymś nowym, często też pomysłodawcy nie doceniają złożoności danej usługi, którą chcą zdefiniować od nowa.

Jednak jestem przekonany, że powstanie wiele usług w oparciu o technologię blockchain, może nie będzie to rewolucja na miarę wynalezienia tranzystora, ale na pewno potencjał technologii jest duży.

###### Mit 4: Transakcje bez prowizji.

Oczywiście możesz stworzyć transakcję, w której nie umieścisz dodatkowej opłaty (*transaction fee*). Ale taka transakcja zostanie odrzucona, ponieważ górnicy (*miners*) wybierają transakcje o największych prowizjach, a liczba transakcji w danym bloku jest ograniczona – w przypadku wygrania wyścigu o nowy blok, suma wszystkich prowizji idzie na konto zwycięskiego górnika. To tłumaczy wszystko. A co tu robią górnicy? Oczywiście górnicy od kryptowalut nie mają nic wspólnego z klasycznymi górnikami. Tak nazywamy ludzi, którzy uczestniczą w tworzeniu kolejnych bloków rejestru transakcji. Dostają za to wynagrodzenie, niejako wydobywają je więc stąd górnicy. Ale wracając do tematu, w skrócie, im większa prowizja tym większe szanse na umieszczenie transakcji w następnym bloku, czyli przekładając na nasz język – transakcja będzie zaksięgowana. Średnie opłaty transakcyjne możesz znaleźć [tutaj](https://bitcoinfees.info/), w chwili pisania tego tekstu wynosiła ona 2,2 USD za transakcję, ale bywało i tak, że wartość ta dochodziła do 37 USD za transakcję. Jak widać nie ma stałej opłaty i jej wartość ma wpływ na prawdopodobieństwo z jakim Twoja transakcja będzie zaksięgowana. Co więcej, opłata transakcyjna nie zależy od kwoty transakcji, więc przy transferowaniu dużych środków małe opłaty nie mają większego znaczenia, ale przy mikropłatnościach sytuacja zmienia się diametralnie.

###### Mit 5: Każdy może zacząć kopać i zarabiać.

Możesz stać się częścią sieci Bitcoin, możesz zacząć kopać, ale nie zarabiać. To znaczy teoretycznie możesz pobierać profity z tej działalności, ale w praktyce to nie takie proste…

Ale po kolei, kopanie (mining) to uczestnictwo w zawodach, które odbywają się średnio co 10 minut. Wygrywa tylko jeden na wszystkich kopiących. Wygrywający zgarnia wszystko, czyli sumę opłat transakcyjnych i dodatkową nagrodę (*mining reward*), dziś jest to 12,5 BTC. Wartość ta z biegiem czasu maleje, aż w końcu w roku 2140 spadnie do zera. Niby mamy jeszcze sporo czasu, ale w chwili obecnej 80% procent jest już wykopana, dlatego konkurencja jest ogromna. Kiedyś mogłeś kopać mając zwykły komputer, potem już musiałeś go uzbroić w wydajne karty graficzne. Następnym krokiem w wyścigu po nagrodę były klastry urządzeń z kartami graficznymi. A dlaczego w ogóle karty graficzne? Ponieważ do tych obliczeń nadają się idealnie, chociaż w tym przypadku nie ma to nic wspólnego z przetwarzaniem obrazu. Jednak teraz nawet i to już nie wystarcza. Dziś należy się uzbroić w specjalistyczny sprzęt wyposażony w sprzętowe jednostki obliczeniowe [ASIC](https://pl.wikipedia.org/wiki/Specjalizowany_uk%C5%82ad_scalony). Ale takich jednostek musisz mieć setki, a może nawet tysiące i będziesz konkurował z gigantycznymi farmami, które pobierają setki kilowatów prądu. Mówi się, że obecny pobór prądu na kopanie jest porównywalny z zapotrzebowaniem średniej wielkości kraju!

Ogólna zasada jest taka: im większą moc obliczeniową posiadasz w sieci BitCoin, tym większe masz prawdopodobieństwo na wygraną. Można jeszcze łączyć się w grupy, a potem dzielić wygraną według wkładu. Jak widzisz nie jest to takie proste jak sugerują prospekty reklamowe…

###### CDN…

W kolejnej części weźmiemy pod lupę [mity wrogów Bitcoina](http://rrowniak.com/it/bitcoin-mity-i-legendy-wrogow/).