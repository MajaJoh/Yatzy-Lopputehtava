# Yatzy-Lopputehtava
Lopputehtävä C++ kurssille
-------------------------------------

Tämä on Yatzyn inspiroima tekstipohjainen noppapeli, jossa pelaaja heittää noppia ja yrittää kerätä pisteitä eri pisteluokista. Peli jatkuu kunnes kaikki pisteytyskategoriat ovat pistettyjä tai jos kelvollisia pisteytysvaihtoehtoja ei ole enään saatavilla.

--- Pelin komponentit ---

 Noppa: 5 kuusisivuista noppaa.
 Pisteluokat: 13 luokkaa.
 Rolls: Pelaajalla on 3 heittoa per vuoro.

--- Pisteytyskategoriat --- 

 Ones: Kaikkien noppien summa, joissa on numero 1.
 
 Twos: Kaikkien noppien summa, joissa on numero 2.
 
 Threes: Kaikkien noppien summa, joissa on numero 3.
 
 Fours: Kaikkien noppien summa, joissa on numero 4.
 
 Fives: Kaikkien noppien summa, joissa on numero 5.
 
 Sixes: Kaikkien noppien summa, joissa on numero 6.
 
 Three of a Kind: Kaikkien noppien summa, jos vähintään kolmessa nopassa on sama numero.
 
 Four of a Kind: Kaikkien noppien summa, jos vähintään neljässä nopassa on sama numero.
 
 Full House: 25 pistettä, jos on yhdistelmä kolmikkoa ja paria.
 
 Small straight: 30 pistettä neljän peräkkäisen numeron sarjasta.
 
 Large straight: 40 pistettä 5 peräkkäisen numeron sarjasta.
 
 Yatzy: 50 pistettä jos kaikissa nopissa on sama numero.
 
 Chance: Kaikkien noppien summa, ei erityisiä vaatimuksia.

--- Ohjeet: ---

 Noppien heittäminen:
 Peli näyttää heitetyt nopat.
 (jos "Enter the positions (1-5) of dice to hold (separated by spaces), or 0 to roll all:" teksti ei näy paina enter)
 
 Sinulla on enintään 3 heittoa per kierros.
 Päätä, mitä noppia pidät ja mitkä heität uudelleen.
 Syötä nopan paikat, joita haluat pitää (1-5) tai syötä 0 heittääksesi kaikki nopat uudelleen.
 esim ( 1 3 4 ) 
 
 Jokaisen heiton jälkeen nykyiset nopan arvot näytetään.

 Pisteluokkien valitseminen:
 Jokaisen kierroksen jälkeen (enintään 3 heittoa) näet jäljellä olevat pisteluokat.
 Peli ehdottaa pisteytysvaihtoehtoja nopan arvojen perusteella.
 Valitse pisteytysluokka syöttämällä vastaava numero.
 Jos kelvollisia pisteytysvaihtoehtoja ei ole, peli ilmoittaa pelaajalle ja päättää vuoron.

 Pisteytys:
 Valitun luokan pisteet lasketaan nopan arvojen perusteella.
 Valittu luokka merkitään pisteytyneeksi ja pisteet päivitetään.

 Pelin loppu:
 Peli päättyy, kun kaikki kategoriat on pisteytetty.
 Kokonaispisteet lasketaan summaamalla kaikkien luokkien pisteet.

 Peli päättyy, kun kaikki kategoriat on pisteytetty, ja lopullinen tulos tulee näkyviin.
