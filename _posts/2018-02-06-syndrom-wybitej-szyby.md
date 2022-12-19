---
id: 58
title: 'Syndrom wybitej szyby'
date: '2018-02-06T08:57:52+00:00'
author: 'Rafał Równiak'
layout: post
guid: 'http://rrowniak.com/?p=58'
permalink: /it-pl/syndrom-wybitej-szyby/
categories:
    - 'Dobre praktyki'
    - IT
    - Management
    - 'Wzorce projektowe'
tags:
    - IT
    - 'syndrom wybitej szyby'
    - zarządzanie
---

[![](https://i1.wp.com/rrowniak.com/wp-content/uploads/2018/02/Broken_windows-1.jpg?resize=590%2C393)](https://i1.wp.com/rrowniak.com/wp-content/uploads/2018/02/Broken_windows-1.jpg)

Drogi Czytelniku chciałbym Ci opowiedzieć o bardzo ciekawym zjawisku z branży IT, określanym, dosyć zresztą zagadkowo, jako syndrom wybitej szyby. Zastanawiasz się zapewne: co to takiego..? Jakie są Twoje pierwsze skojarzenia? Być może staje Ci przed oczami stary, opuszczony dom na uboczu, albo grupa łobuzów rzucających kamieniami w wystawy sklepowe. Dobrze! Jesteś bardzo blisko! Jeśli twoja wyobraźnia poprowadzi Cię jeszcze o krok dalej, do mrocznych, owianych złą sławą zakamarków miasta znajdziesz się u celu. Rzeczywiście geneza tego syndromu bierze się z badań kryminalistycznych dotyczących dzielnic i przedmieść, gdzie panuje duża przestępczość, a wybijanie szyb jest ulubioną rozrywką stałych bywalców. Ulubioną, ale zapewne nie jedyną, należałoby dodać. Zastanawiasz się zapewne jaki związek ma kryminalistyka z branżą oprogramowania i czy w IT jest tak źle, że trzeba się uciekać do doświadczeń stróżów prawa, i to tych najgorszych? No cóż, może tak źle nie jest, ale zacznijmy od początku.

  
Syndrom ten powstał na podstawie prostej obserwacji. Zauważono, że w dzielnicach, w których panuje porządek, wszystko jest na swoim miejscu, nie ma tytułowych powybijanych szyb, przestępczość utrzymuje się na stałym, z reguły niskim, poziomie. Jednak wystarczy jeden akt wandalizmu, jedna wybita szyba, aby liczba przestępczych incydentów zaczęła wzrastać.

Tłumaczy się to tym, że ludzie łatwiej popełniają przestępstwa w otoczeniu, które nosi ślady wcześniejszych aktów wandalizmu. Otoczenie takie niejako zachęca do takich czynów, a wcześniejsze ślady sugerują, że nie ma nikogo, kto by czuwał nad tym miejscem i odpowiednio reagował na takie zdarzenia. Generuje to poczucie bezkarności i sygnalizuje, że panuje tu bezprawie.

Teraz analogia zaczyna być widoczna. W projektach informatycznych też może panować bezprawie, tylko symptomy są inne. Nie ma wybitych szyb, ani graffiti na budynkach, ale jest źle napisany kod, prowizorki i obejścia problemów, brak komentarzy, tam gdzie powinny być, niedziałające i nieaktualne unit testy (lub ich brak), nie stosowanie się do standardów kodowania, zdezaktualizowana dokumentacja. Brzmi znajomo? Takich zaniechań może być jeszcze więcej! Te wydaje się niby „małe grzeszki”, popełnione przez kogoś z lenistwa lub niedbalstwa działają jak ta pierwsza, wybita szyba, zachęcają do podobnych działań, do powielania starych zaniechań. Na ogół widząc taki stan rzeczy nowi programiści tracą zapał i motywację. Po jakimś czasie poddają się i przyjmują istniejący styl.

Kiedy stopień entropii osiągnie pewną masę krytyczną pojawia się opinia, że projekt jest nie do odratowania. Zaczyna się powszechne narzekanie. Zniechęcenie. Ci bardziej rewolucyjnie nastawieni koledzy przebąkują o potrzebie przepisaniu całego systemu. I być może wszyscy mają rację. Choć nie jest to takie proste…

Oczywiście ktoś mógłby od razu powiedzieć jakie należy wykonać kroki, aby uzdrowić sytuację. Takich porad jest mnóstwo i brzmią mniej więcej tak: poprawić testy, wprowadzić przeglądy kodu, zarządzić refactoring kodu, zmienić metodykę wytwarzania oprogramowania lub ostatecznie przepisać system. Proste, co nie? Ale ktoś z doświadczeniem, szczególnie managerskim wie, że tylko w teorii. Ponieważ tylko w teorii praktyka to teoria. I podobnie jest tutaj. Bo na przykład jak wytłumaczyć zarządowi, że projekt który zarabia i nie jest specjalnie rozwijany oprócz utrzymania i drobnych zmian, musi być mocno przewałkowany (lub przepisany w skrajności)? To z reguły nie przejdzie, ponieważ decydenci mają inny punkt widzenia i wbrew powszechnej opinii, jaka panuje w środowisku deweloperskim, decyzje podejmowane na wyższych szczeblach nie zawsze są błędne. Nawet przekonanie zarządu do spłaty długu technicznego, przed rozpoczęciem poważniejszych robót, nie zawsze jest łatwe, a co dopiero mówić o całkowitym przepisaniu systemu.

Co zatem zrobić? Nie ma jednoznacznej odpowiedzi, ponieważ wiele zależy od różnych czynników, często tych ludzkich, które nie poddają się logice i zdrowemu rozsądkowi. Jednak z mojego doświadczenia wynika, że najlepszym sposobem jest praca u podstaw, naprawa kolejnych wybitych szyb, pilnowanie aby nie przybywało nowych. Ewolucja zamiast rewolucji. A jeśli nie jest to możliwe i czujesz się z tym niekomfortowo – może już czas aby pomyśleć nad zmianą?