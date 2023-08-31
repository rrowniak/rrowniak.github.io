---
id: 290
title: 'Security through obscurity: antywzorzec czy przemysłowy standard?'
date: '2018-05-13T15:55:43+00:00'
author: 'Rafał Równiak'
layout: post
guid: 'http://rrowniak.com/?p=290'
permalink: /dobre-praktyki/security-through-obscurity-antywzorzec-czy-przemyslowy-standard/
image: /wp-content/uploads/2018/05/alchemist.jpg
categories:
    - 'Architektura oprogramowania'
    - 'Dobre praktyki'
    - 'Wzorce projektowe'
tags:
    - AES
    - 'bezpieczeństwo przez niejawność'
    - HITAG2
    - immobilizer
    - kryptografia
    - 'Security through obscurity'
---

[Security through obscurity](https://en.wikipedia.org/wiki/Security_through_obscurity) to oczywiście angielskie określenie, które można przetłumaczyć jako [bezpieczeństwo przez niejawność](https://pl.wikipedia.org/wiki/Security_through_obscurity). Ale o co chodzi? Czy jest to antywzorzec czy może przemysłowy standard? I co ma z tym wspólnego immobilizer w Twoim aucie? Jeśli chcesz poznać odpowiedzi na te pytania – zapraszam do czytania.

## Bezpieczeństwo przez niejawność

Bezpieczeństwo przez niejawność (ang. *security through obscurity*) to zestaw praktyk polegających na ukrywaniu algorytmów, protokołów i formatów służących do szyfrowania i wymiany danych. Główną motywacją jest prosta zasada: nie znasz algorytmu użytego do szyfrowania danych zatem nie odszyfrujesz ich. Brzmi sensownie.

Zanim przejdziemy do szczegółów pozwolę sobie na mały przykład. Wyobraź sobie, że żyjesz w czasach gdzie skrzaty, mamuny i leśne nimfy nie zostały jeszcze wyparte przez prawa hydrauliki, prawa dynamiki społecznej, prawa tego i owego. W czasach gdy jedynym sposobem na komunikację zdalną jest napisanie listu i podanie go gońcowi. Jednak jako szanujący się alchemik nie chciałbyś aby ktoś trzeci poznał korespondencję jaką prowadzisz z kolegą po fachu. Czyli list trzeba jakoś zaszyfrować. Pierwszym pomysłem jaki może przyjść Ci do głowy jest skonstruowanie specjalnego algorytmu, który każdej literze alfabetu przyporządkuje inną np. f(*A) = J*, f(*B)* = *A*, itp. Kiedy algorytm będzie gotowy musisz spotkać się z przyjacielem i objaśnić mu wszystkie szczegóły. Potem możesz rozpocząć szyfrowaną korespondencję. Jak widać podstawowym założeniem jest tajność algorytmu, czyli mamy klasyczny przykład bezpieczeństwa przez niejawność.

Niestety taka metoda ma kilka wad. Wyobraź sobie, że masz kilku znajomych alchemików, z którymi chcesz prowadzić szyfrowaną korespondencję i chciałbyś aby koledzy nie mogli sobie nawzajem rozszyfrowywać wiadomości. Trzeba zatem dla każdego z osobna wymyślić nowy algorytm lub mocno zmodyfikować obecny. Sprawa co najmniej mocno uciążliwa, ale to nie koniec problemów. Algorytm jest tajny więc nie możesz go przedstawić szerszej grupie specjalistów, aby spojrzeli na niego krytycznym okiem. I w naszym przypadku jest to kardynalny błąd ponieważ metoda jaką zastosowaliśmy jest bardzo łatwa do złamania. Pewnie pomyślisz „przecież to był naiwny algorytm, ja zrobię taki nie do złamania”. No cóż, wielu tak myślało i chyba domyślasz się jak to się skończyło…

W takim razie jak można zrobić to inaczej? Z pomocą przyjdzie szyfrowanie z użyciem klucza. Algorytm będzie jawny i ogólnie dostępny. Tylko klucz będzie utajniony. Klucz czyli albo duża liczna (najlepiej losowa) albo jakiś fragment tekstu, coś na podobieństwo hasła. Teraz wygenerujesz różne klucze dla swoich znajomych, a algorytm zostanie bez zmian. Co więcej, możesz uzgodnić ze znajomym jaki algorytm będzie najodpowiedniejszy. Ponieważ niektóre metody mogą być bardzo złożone, Twój znajomy może preferować te o mniejszej złożoności. Podobnie działają współczesne protokoły i tą część odpowiedzialną za dogadywanie się nazywamy [handshake](https://pl.wikipedia.org/wiki/Handshake).

Mam nadzieję, że przekonałem Cię, że tworzenie własnego algorytmu kryptograficznego, który ma być częścią *bezpieczeństwa przez niejawność* to bardzo zły pomysł. Ogólna zasada w inżynierii oprogramowania mówi: „*nigdy, przenigdy nie twórz własnego algorytmu kryptograficznego, który miałby być użyty w poważnych zastosowaniach*„. Dlaczego? Odpowiedź jest prosta: bo istnieją lepsze metody, których solidność została udowodniona w praktyce i ich implementacje przeszły niezliczone próby bojowe.

## Przemysł

Tytuł sugeruje jakoby przemysł chętnie uciekał się do bezpieczeństwa przez niejawność. I taka niestety jest rzeczywistość. Przykładów takich pomysłów znajdziesz wiele z opisem wyjaśniającym co poszło nie tak, czyli dlaczego nie warto iść tą ścieżką. Błąd ten jest często popełniany na wyższych szczeblach, gdzie decydenci intuicyjnie zakładają, że tajny algorytm stworzony w naszej firmie, gdzie przecież pracują najlepsi inżynierowie na świecie, to w oczywisty sposób bezpieczne rozwiązanie. Jawność algorytmów kryptograficznych jest podejrzana. Bo jak coś może być bezpieczne skoro każdy ma do tego wgląd? Byłem uczestnikiem wielu takich dyskusji, więc niestety wiem jak trudno jest przekonać kogoś do użycia klasycznych i znanych algorytmów.

Tutaj należy wspomnieć o jednej bardzo ważnej rzeczy. To że używamy jawnego i znanego protokołu nie oznacza, że musimy się dzielić z całym światem tym jaki algorytm wybraliśmy do realizacji danego zadania. Ale to i tak będzie w najlepszym razie tylko lekkim utrudnieniem dla hackera.

Żeby nie być gołosłownym posłużę się przykładem, który pokazuje skalę problemu.

## Immobilizer

Tego skrótu chyba nie muszę nikomu tłumaczyć, hhociaż zasada działania może być już słabiej znana. W uproszczeniu: w kluczyk wbudowany jest mały układ elektroniczny sparowany z elektroniką pojazdu. W momencie włożenia kluczyka do stacyjki elektronika pojazdu (np. [ECU](https://pl.wikipedia.org/wiki/Sterownik_silnika)) sprawdza czy kluczyk jest „sparowany”. Jeśli tak to jedziemy, jeśli nie to silnik nie odpali, czyli kradzież auta jest niemożliwa. W teorii, ale po kolei.

Przemysł motoryzacyjny znany jest z dość konserwatywnego podejścia do nowych technologii. I pewnie jest w tym szaleństwie jakaś metoda, jednak razem z konserwatyzmem idzie w parze podejście „*wszystko robimy sami, nasi inżynierowie umieją projektować auta to i poradzą sobie z IT*” (od jakiegoś czasu można zaobserwować pozytywne zmiany w tej materii – nareszcie!). Oczywiście nie ominęło to immobilizerów, które padły ofiarą choroby zwanej *bezpieczeństwem przez niejawność* (więcej możesz znaleźć [tutaj](http://ww1.microchip.com/downloads/en/DeviceDoc/article_open_immob_system.pdf)). I jakie były rezultaty?

Za pewne słyszałeś o historiach w których mówi się, że złodziej potrzebuje kilku sekund na odpalenie auta, może oglądałeś filmiki jak ktoś z laptopem na kolanach odpala furę wartą kilkaset tysięcy złoty, a może byłeś ofiarą takiej kradzieży. Wielkim paradoksem jest to, że często immobilizery są dużym utrapieniem użytkowników ,bo procedura przekodowania i spasowania jest najczęściej koszmarem (drogim koszmarem).

Przykładem może być standard [HITAG2](https://en.wikipedia.org/wiki/Crypto-1). Algorytm jest tajny, ale został odtworzony i okazało się, że jest stosunkowo łatwy do złamania. [Tutaj](https://www.usenix.org/system/files/conference/usenixsecurity12/sec12-final95.pdf) możesz poczytać o szczegółach.

Jak to możliwe? Czy dzisiejsza technologia IT nie oferuje nic pewniejszego? Oczywiście, że oferuje. Są sposoby „parowania” praktycznie nie do złamania. Część producentów już z nich korzysta. Przykładem takiego algorytmu jest [AES-128](https://pl.wikipedia.org/wiki/Advanced_Encryption_Standard). Oczywiście to tylko jeden fragment większej układanki i problematyka jest o wiele bardziej złożona. Należy również pamiętać, że ukryty algorytm wcześniej czy później zostanie złamany (patrz HITAG2) albo wycieknie. Nie tędy droga.

Jeden antywzorzec a tyle problemów. Mam nadzieję, że już wiesz czym pachnie *security through obscurity*…