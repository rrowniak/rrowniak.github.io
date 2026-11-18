---
id: 706
title: 'Witaj w piekle: C &#038; C++ &#8211; niejawne konwersje i promocje typów'
date: '2020-05-22T11:34:06+00:00'
author: 'Rafał Równiak'
layout: post
guid: 'http://rrowniak.com/?p=706'
permalink: /dobre-praktyki/witaj-w-piekle-c-c-niejawne-konwersje-i-promocje-typow/
image: /wp-content/uploads/2020/05/neonbrand-small-unsplash.jpg
categories:
    - C
    - C++
    - 'Dobre praktyki'
tags:
    - C
    - c++
    - Konwersje
    - Promocje
    - Typy
---

Nie jest tajemnicą, że C i C++ zawiera sporo różnych pułapek czyhających nawet na doświadczonych programistów. Chciałbym przedstawić kilka wyjątkowo wrednych, trudnych do wykrycia, czasem subtelnych i prawie zawsze bardzo niebezpiecznych niespodzianek jakie zaserwuje nam kompilator. Co gorsza, na pierwszy rzut oka wszystko wygląda logicznie…

Na początek kilka przykładów, które z jakiegoś powodu są uwielbiane przez technicznych rekruterów C++…

### Przykład 1

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: cpp; title: ; notranslate" title="">
unsigned char one = 1;
unsigned char max = 255;
     
unsigned char sum = one + max;
    
if (sum == one + max) {
    std::cout << "Captain obvious!" << std::endl;
} else {
    std::cout << "Wait... WTF?" << std::endl;
}
```

</div>### Przykład 2

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: cpp; title: ; notranslate" title="">
unsigned char x = 0;
unsigned char y = 1;
printf("255, right? Oops: %u\n", x - y);
```

</div>### Przykład 3

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: cpp; title: ; notranslate" title="">
unsigned int a = 1;
signed int b = -2;

if (a + b > 0) {
    std::cout << "Wait... -1 > 0?" << std::endl;
}
```

</div>## Analiza

Aby zrozumieć powyższe *anomalie* trzeba zapoznać się z trzema konceptami wprowadzonymi przez standardy C i C++: promocje typów całkowitych, [niejawne konwersje](https://en.cppreference.com/w/cpp/language/implicit_conversion) i balansowanie. Oczywiście jest to tylko wierzchołek góry lodowej ale z mojego doświadczenia wiem, że nieznajomość właśnie tych reguł przyczynia się do największej ilości błędów tego rodzaju. Postaram się ująć obydwa języki (C i C++) w jedną całość jako że reguły te są niemal identyczne.

#### Promocje typów całkowitych i NIEJAWNE KONWERSJE

Każdemu typowi całkowitemu przydzielono rangę konwersji (*conversion rank*), która to wykorzystywana jest do podjęcia decyzji przez kompilator o promocji. I tak dla typów podstawowych, w kolejności od najmniejszych do największych rang mamy: `char`, `short`, `int`, `long`, `long long`. Odpowiadające im typy `unsigned` mają identyczne rangi.

Zasada jest taka, że każdy typ całkowity (w tym `unsigned`) o randze mniejszej niż `int` jest **niejawnie konwertowany w wyrażeniach** do typu `int` pod warunkiem, ze `int` jest wstanie reprezentować każdą wartość typu konwertowanego. Czyli konwersja nie spowoduje utraty wartości. Jeśli jednak ten warunek nie zostałby spełniony to konwersja będzie dokonana do typu `unsigned int`.

Powyższą regułę nazywamy **promocjami typów całkowitych** (*integer promotions*).

Uzbrojeni w tą wiedzę możemy przeanalizować *przykład nr 1*. Interesujący nas fragment to `if (sum == one + max)`. Zmienne `sum`, `one` i `max` są typu `unsigned char` więc zgodnie z regułą promocji będą one promowane w wyrażeniach do typu `int`. Możemy zapisać to wyrażenie równoważnie jako `if ((int)sum == (int)one + (int)max)`. Pamiętając, że wcześniej zmienna `sum` przyjmuje wartość `0` po rzutowaniu wyniku dodawania z `int` na `unsigned char` (znowu reguła promocji `sum = (int)one + (int)max`!). Dla odmiany wyrażenie w warunku `(int)one + (int)max` będzie mieć wartość 256. Stąd to dziwne zachowanie.

*Przykład 2* pozostawiam jako ćwiczenie. Reguła promocji tłumaczy dziwny rezultat (`255, right? Oops: 4294967295`). Tutaj trzeba również zwrócić uwagę na flagi formatujące w funkcji `printf`.

#### Balansowanie

*Przykład 3* jest ciekawy bo dziwnego zachowania już nie wyjaśnimy powyższymi prawidłami. Mamy dwa typy o równych rangach: `signed int` i `unsigned int`. Co w takim przypadku? Musimy zapoznać się z tzw. balansowaniem (*balancing*) a bardziej precyzyjnie z *Usual arithmetic conversions*.

Większość operatorów binarnych (np. `+`) działających na typach liczbowych przyjmuje dwa argumenty tego samego typu i zwraca ten sam typ. Typ ten nazywamy *common real type*. Koncepcyjnie moglibyśmy przedstawić taki operator jako

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: cpp; title: ; notranslate" title="">
template <class T>
T operator+(T a, T b)
{ return a + b; }
```

</div>Więc jeśli wystąpi różnica typów argumentów mających tą samą rangę, tak jak w przykładzie 3, to musi zostać dokonana konwersja. W przypadku różnych rang mniejszych od `int` zostanie wykonana promocja i operator może otrzymać na wejściu dwa identyczne typy (`int` albo `unsigned int`). A co w innych przypadkach?

Balansowanie wykonywane jest wg. poniższego algorytmu (skup się!):

- Jeśli jeden z argumentów jest `long double` to drugi będzie konwertowany do `long double` (np. `long double + float ==> long double`)
- W przeciwnym wypadku, jeśli jeden z argumentów jest `double` to drugi będzie konwertowany do `double` (np. `double + int ==> double`)
- W przeciwnym wypadku, jeśli jeden z argumentów jest `float` to drugi będzie konwertowany do `float` (np. `unsigned long long int + float ==> float`)
- W przeciwnym przypadku (typy całkowite) **zastosuj promocję typów całkowitych** (opisaną powyżej) **\_i\_**:
    - Jeśli typy są identyczne – koniec zabawy
    - W przeciwnym wypadku, jeśli rangi są różne ale wersje typów (`unsigned`/`signed`) takie same to konwertuj do typu o większej randze (np. `int + long ==> long`)
    - W przeciwnym wypadku, jeśli wersje typów są różne i ten „`unsigned`” ma większą bądź równą rangę to konwertuj do tego typu (`unsigned int + int ==> unsigned int`)
    - W przeciwnym wypadku, jeśli ranga typu „`signed`” jest wyższa to skonwertuj do typu „`signed`” pod warunkiem, że ten pomieści drugi typ w całości (`signed long long + unsigned int ==> signed long long`)
    
    
    - W przeciwnym wypadku (ranga typu „`signed`” jest wyższa niż typu „`unsigned`” ale „`signed`” nie pomieści w całości „`unsigned`„) to konwertuj obydwa typy do nowego typu „`unsigned`” o randze równej „`signed`” (np. jeśli `sizeof(long) == sizeof(long long)` to `unsigned long int + signed long long int ==> unsigned long long int`)
    - Uff

Jak można poprawić przykład 3? Np. zmieniając `unsigned int a = 1;` and `unsigned short a = 1;`.

Na koniec kilka przykładów.

1\.

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: cpp; title: ; notranslate" title="">
double d = 1;
int e = 2;
unsigned int f = 3;
    
auto g = d * (e / f);

// g=? => 1!

auto h = d * e / f;

// h=? => ~0.666667  :)
```

</div>2\.

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: cpp; title: ; notranslate" title="">
int a = -2;
unsigned int b = 1;
    
auto c = a + b;

// c=? => 4294967295
```

</div>Jeśli w powyższym przykładzie zmienimy linię 1 na `int a = -1;` to dostaniemy poprawny wynik. Dlaczego?

3\.

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: cpp; title: ; notranslate" title="">
long int a = -2;
unsigned int b = 1;
    
auto c = a + b;

// c=? => -1
```

</div>4\.

<div class="wp-block-syntaxhighlighter-code ">```
<pre class="brush: cpp; title: ; notranslate" title="">
static_assert(sizeof(long) == sizeof(long long), " ");

unsigned long f = 1;
long long g = -2;

auto h = f + g;
std::cout << "-1?.... " << h << std::endl;
// h (unsigned long long) --> 18446744073709551615
```

</div>Ostatni przykład pokazuje ostatnią regułę balansowania w akcji.

Mam nadzieję, że temat został choć odrobinę przybliżony. Nie jest to kompendium wiedzy ale raczej wstęp do tematyki. Z drugiej strony informacje zawarte w tym wpisie pozwolą na uniknięcie 90% nieprzyjemności jakie napotkamy w tym obszarze.

## Materiały dodatkowe:

[https://en.cppreference.com/w/cpp/language/implicit\_conversion](https://en.cppreference.com/w/cpp/language/implicit_conversion)

<figure class="wp-block-embed is-type-link is-provider-jeff-hurchalla"><div class="wp-block-embed__wrapper">[\[C/C++\] Surprises and Undefined Behavior From Unsigned Integer Promotion](https://jeffhurchalla.com/2019/01/16/c-c-surprises-and-undefined-behavior-due-to-unsigned-integer-promotion/)</div></figure><https://stackoverflow.com/questions/46073295/implicit-type-promotion-rules>