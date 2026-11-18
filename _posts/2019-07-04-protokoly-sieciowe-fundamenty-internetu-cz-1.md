---
id: 609
title: 'Protokoły sieciowe &#8211; fundamenty Internetu cz.1'
date: '2019-07-04T17:41:01+00:00'
author: 'Rafał Równiak'
layout: post
guid: 'http://rrowniak.com/?p=609'
permalink: /sieci/protokoly-sieciowe-fundamenty-internetu-cz-1/
image: /wp-content/uploads/2019/05/david-klein-452056-small.jpg
categories:
    - Sieci
tags:
    - ethernet
---

*Jak działa internet?* To niewinnie wyglądające pytanie jest w rzeczywistości bardzo trudne. Internet to właściwie zbiór niezliczonej ilości technologii, które to jakimś cudem razem współdziałają. Ta współpraca jest możliwa dzięki (w miarę) dobremu dogadywaniu się, za co odpowiadają tzw. protokoły sieciowe. Liczba protokołów sieciowych może przyprawić o zawrót głowy. Wiele z nich działa na różnych poziomach i w różnych sytuacjach, co na pewno nie ułatwia zadania polegającego na sprawnym nawigowaniu w tym pogmatwanym świecie. Spróbujmy zatem skatalogować kilka najbardziej popularnych protokołów wraz z ich krótkim opisem i wybranymi cechami.

 Na szczęście sposób uporządkowania tego uniwersum został odkryty znacznie wcześniej i właśnie z tego powodu powstał tzw. [warstwowy model sieci OSI](https://pl.wikipedia.org/wiki/Model_OSI). Niejako rozbija on całe zagadnienie na kilka podproblemów, które stają się warstwami nakładającymi na siebie. Każda z nich definiuje inne odpowiedzialności. I tak, najniższa warstwa to:

### Warstwa 1: fizyczna (Physical Layer)

Jak sama nazwa sugeruje, tutaj zdefiniowane jest medium po którym będzie odbywał się transport danych wraz z różnymi charakterystykami i parametrami, takimi jak rodzaj transmisji (half-duplex, full-duplex), poziomy napięć (mogą one być definiowane poprzez protokoły takie jak TTL), długości linii, długość fali, częstotliwość taktowania, częstotliwość fali elektromagnetycznej, modulacja itp. Tych parametrów jest setki jak nie tysiące. Ale nie jest to zbytnio ciekawe z punktu widzenia inżyniera oprogramowania. Warto jednak wiedzieć, że **istota tej warstwy polega na umożliwieniu przesyłania bitów z jednej maszyny do drugiej**. Sama struktura danych nie jest tutaj zdefiniowana. Przykłady takich protokołów? Proszę bardzo: [IRDA](https://en.wikipedia.org/wiki/Infrared_Data_Association) (warstwa fizyczna), [USB](https://en.wikipedia.org/wiki/USB) (warstwa fizyczna), [RS-232](https://en.wikipedia.org/wiki/RS-232), [100BASE-T](https://en.wikipedia.org/wiki/100BASE-T) (warstwa fizyczna), [802.11](https://en.wikipedia.org/wiki/802.11) [Wi-Fi](https://en.wikipedia.org/wiki/Wi-Fi), [CAN bus](https://en.wikipedia.org/wiki/CAN_bus) (warstwa fizyczna). To oczywiście tylko kilka przykładów.

### Warstwa 2: łącza danych (Data Link Layer)

Tutaj zaczyna się robić naprawdę ciekawie. **Warstwa ta definiuje w jaki sposób dwie maszyny połączone fizycznym medium będą przesyłać „atomowe” paczki danych**. Te atomowe paczki danych nazywamy ramkami (*frames*). Krótko mówiąc – wykorzystując warstwę pierwszą będziemy przesyłać dane mające już pewną strukturę. Najczęściej protokoły tej warstwy są implementowane przez sprzęt, jak na przykład karty sieciowe. Ale nie przynudzając zbytnio z teorią przejdźmy do konkretnych protokołów, a sprawa się rozjaśni.

#### Ethernet

To najbardziej popularny protokół warstwy drugiej. Jednak protokół ten dostępny jest w wielu wariantach różniących się między sobą pewnymi szczegółami. Oto niektóre z tych wariantów: Ethernet II, Ethernet 802.3raw, Ethernet IEEE 802.3, Ethernet IEEE 802.3 SNAP, VLAN 802.1q – Ethernet II tagged i IEEE 802.3 tagged. Najbardziej popularnymi wariantami są Ethernet IEEE 802.3 (+ jego „pod-wariant” – 802.3 tagged, który wykorzystywany jest w sieciach wirtualnych VLAN) i Ethernet II.

Omówmy zatem IEEE 802.3 i Ethernet II.

<figure class="wp-block-image">![Representation of an Ethernet 802.3 frame structure](https://i0.wp.com/www.ionos.com/digitalguide/fileadmin/DigitalGuide/Screenshots_2018/EN-ethernet-frame-structure3.jpg?w=696&ssl=1)<figcaption>Ethernet IEEE 802.3</figcaption></figure><figure class="wp-block-image">![Representation of an Ethernet II frame structure](https://i1.wp.com/www.ionos.com/digitalguide/fileadmin/DigitalGuide/Screenshots_2018/EN-ethernet-frame-structure.jpg?w=696&ssl=1)<figcaption>Ethernet II</figcaption></figure>Sekcje *Preamble* i *Inter Frame Gap* są częścią warstwy 1. Nas interesuje część zwana *Ethernet Frame* (ramka ethernetowa). Ramki ethernetowe mają zmienny rozmiar w granicach od 64 bajtów do 1518 bajtów (wyjątkiem mogą być tzw. [jumbo frames](https://en.wikipedia.org/wiki/Jumbo_frame)) a więc rozmiar danych przesyłanych wynosi od 42/46 bajtów do 1497/1500 bajtów dla IEEE 802.3/Ethernet II. To drugie ograniczenie mówiące o maksymalnym rozmiarze danych w ramce nazywa się **MTU** (Maximum Transmission Unit).

Patrząc na strukturę ramki widzimy, że pierwsze 12 bajtów to adresy **MAC**: docelowy i źródłowy. Adresy pozwalają na dostarczanie ramek do konkretnych odbiorców – jednym fizycznym medium może być połączone więcej niż dwie maszyny. Później sobie omówimy skąd nowo podłączona maszyna zna adres docelowy, co to są adresy rozgłoszeniowe i jakie urządzenia operują na tej warstwie.

Kolejne pole to Length (IEEE 802.3) czyli rozmiar danych w sekcji Data. Oczywista sprawa… Otóż nie do końca. Pole Length może być różnie interpretowane a to w związku z zapewnieniem kompatybilności z Ethernet II, a właściwie wykryciem czy mamy do czynienia z ramką IEEE 802.3 czy z Ethernet II. Jeśli wartość tego pola jest mniejsza lub równa 1536 to istotnie jest to rozmiar danych w ramce i zarazem ramka IEEE 802.3. Jednak w przeciwnym wypadku pole to będzie interpretowane jako typ protokołu warstwy 3 (np. IP, MPLS, ICMP itp) a sama ramka będzie interpretowana jako Ethernet II. Widać to dobrze porównując oba formaty. Warto zauważyć, że jeśli wartość ta będzie z przedziału \[1498 – 1535\] to mamy do czynienia z przypadkiem niezdefiniowanym.

Jak już wspomniałem pole Type w Ethernet II oznacza protokół warstwy trzeciej. Pełną listę wspieranych typów można zobaczyć [tutaj](https://en.wikipedia.org/wiki/EtherType). Wariant IEEE 802.3 niestety jest nieco bardziej złożony jeśli chodzi wyznaczenia EtherType. Służy do tego pole [DSAP](https://www.savvius.com/networking-glossary/reference_overview/sap_numbers/). Jednak jest to tylko jeden bajt więc liczba protokołów była by ograniczona do 256. Jest pewna furtka – jeśli wartość tego pola wynosi 0xAA to mamy do czynienia z wariantem IEEE 802.3: SNAP. I tam są zdefiniowane kolejne pola pozwalające na odkodowanie typu. Ale myślę, że nie ma sensu wchodzić w tak głębokie szczegóły.

Pozostaje jeszcze jedno pytanie: **jak nowo podłączony komputer do sieci ma zaadresować pierwszą ramkę**? Istnieje specjalny adres MAC: FF:FF:FF:FF:FF:FF. To nic innego jak adres rozgłoszeniowy – tak zaadresowana ramka dotrze do każdego urządzenia podłączonego do tego samego switcha. Mamy tutaj do czynienia z rozgłoszeniowym trybem transmisji (broadcasting). Jednak ten mechanizm staje się użyteczny dopiero w połączeniu z innymi protokołami takimi jak ARP lub DHCP. Ale o tym później.

#### Inne protokoły

Mamy kilka innych protokołów ale najczęściej, obok Ethernet, używanym jest [IEEE 802.11](https://en.wikipedia.org/wiki/IEEE_802.11) WiFi. Jest to odpowiednik Ethernet dla WiFi. Pozostałe z nich są specjalistyczne i rzadziej używane (np. VLAN) więc nie będę przynudzał nimi zbytnio.

### Warstwa 2.5: WTF?

Tak, to nie pomyłka. Co prawda nie ma czegoś takiego jak warstwa 2.5 ale w żargonie mówi się o protokołach warstwy 2.5. Są twory, które wykorzystują warstwę 2 (głównie Ethernet) ale z drugiej strony nie spełniają definicji warstwy 3. Przykładem jest [MPLS](https://en.wikipedia.org/wiki/Multiprotocol_Label_Switching) służący do szybkiego trasowania pakietów, którego nie będziemy opisywać bo mamy znacznie ciekawszy i częściej używany w praktyce protokół:

#### ARP (**Address Resolution Protocol**)

Protokół ten służy do logicznego mapowania adresów MAC (warstwa 2) z adresami IP warstwy trzeciej (chociaż mogą to być inne adresy niż IP). Kiedy go potrzebujemy? Ano wtedy gdy mając już jakiś docelowy adres IP (np. 192.168.1.2) chcemy wysłać odpowiedni pakiet do tego adresata. Ale jaki docelowy adres MAC należy wstawić w ramce? I czy będzie on adresem docelowego hostu? Na drugie pytanie można odpowiedzieć szybko – z reguły nie będzie on adresem docelowego hostu, no chyba, że taka maszyna znajduje się w tej samej sieci lokalnej i nie jest oddzielona żadnymi routerami czy bramami.

Jak zatem działa ten protokół? Załóżmy, że komputer *A* chce wysłać pakiet do komputera *B*. Z usługi DNS *A* dowiedział się, że adres IP *B* to 192.168.1.2. Ale podczas konstrukcji pakietu wymagany jest adres MAC tej maszyny (*B*) lub węzła pośredniczącego w komunikacji. Więc komputer A:

<div class="wp-block-advgb-list">- Wysyła zapytanie ARP gdzie adres docelowy MAC to FF:FF:FF:FF:FF:FF. Czyli takie zapytanie trafi do wszystkich komputerów w sieci lokalnej. Zapytanie to można tłumaczyć mniej więcej tak: czy ktoś zna adres MAC odpowiadający takiemu adresowi IP 192.168.1.2?
- Jeśli maszyna B otrzyma rozgłoszone zapytanie to niezwłocznie odpowiada: tak to ja, mój MAC jest taki a taki.
- Może się zdarzyć, że maszyna B leży w innej podsieci i nie otrzyma tej wiadomości. Ale jest szansa, że router lub inny węzeł sieci będzie wiedział jak przekierować pakiet do B. Wtedy odpowie: wysyłaj te pakiety na ten MAC…

</div>Aby za każdym razem nie pytać się niepotrzebnie o te same adresy wymyślono coś takiego jak tablica ARP (ARP table). To taka pamięć podręczna na lokalnej maszynie uaktualniana z każdym otrzymanym zapytaniem lub odpowiedzią. Wtedy potrzeba wysyłania zapytań maleje z czasem. Taką tablicę można również ręcznie „tuningować”.

Ok, mamy już podstawy. To tyle na dzisiaj. W następnej części zajmiemy się kolejnymi protokołami i warstwami.