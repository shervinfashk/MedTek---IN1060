
# MedTek - Teknisk Rapport

### [Video-demo](https://drive.google.com/file/d/1RUjJMyyZV4dEII6PD99wNJM0WbJ0Mjwz/view?usp=sharing) 

### [Prosjektside](https://www.uio.no/studier/emner/matnat/ifi/IN1060/v24/prosjektgrupper/medtek/)

## Hvordan fungerer løsningen?
Løsningen fungerer ved å bruke Arduino til å oppdage og reagere på nærliggende objekter. Ved hjelp av ultrasoniske sensorer måler systemet avstander til både åpningen og eventuelt søppel.

Disse sensorene sender ut lydbølger og måler tiden det tar før de reflekteres tilbake. Basert på denne tiden kan systemet beregne avstanden til objektene. Denne informasjonen brukes deretter til å styre en servo-motor, piezo og LED-belysning. I tillegg er det lagt til mulighet til å manuelt overstyre åpne/lukke funksjonen og om artefakten skal lage lyd.

Når systemet er aktivt, kan man oppleve følgende:
* Hvis en tilstanden til “flip-switchen” endres av en bruker vil servoen åpne lokket frem til denne tilstanden endres igjen
* Når ingen objekter er i nærheten av åpningen, forblir servo lukket for å hindre uønsket tilgang.
* Hvis en person eller et objekt nærmer seg åpningen og det ikke er søppel i nærheten, vil servo åpnes automatisk.
* Hvis søppel blir detektert i nærheten av åpningen, vil systemet gi en lyd- og lysvarsling for å signalisere behovet for å fjerne søppelet.
* Når søppelet er fjernet og ingen objekter er i nærheten, vil servo lukkes igjen.

---

## Kretstegning, kretsdiagram og komponenter 

![Skjermbilde 2024-05-13 132127](https://github.com/shervinfashk/MedTek---IN1060/assets/110855795/63346007-3cb1-4b8e-a881-728bdb0e876a)

![Skjermbilde 2024-05-13 132157](https://github.com/shervinfashk/MedTek---IN1060/assets/110855795/c1144dc9-5eac-40fc-aea5-cd2b56aef71d)

![Skjermbilde 2024-05-13 144408](https://github.com/shervinfashk/MedTek---IN1060/assets/110855795/e090ef21-20e8-4592-be22-57db3eded07b)

---

## Funksjoner

* maalAvstandFelles(): Denne funksjonen måler avstanden ved hjelp av begge ultralydsensorene. Den bruker disse avstandsmålingene til å oppdatere variabler som representerer avstanden til åpningen og søppel. Disse avstandsverdiene blir deretter konvertert til centimeter ved hjelp av en annen funksjon.

* maalAvstandIndividuelt(): Denne funksjonen er ansvarlig for å måle avstanden ved hjelp av en enkelt ultralydssensor. Den sender ut et ultralydssignal, venter på ekkoet, og måler tiden det tar for ekkoet å returnere. Basert på denne tiden, beregner den avstanden til objektet foran sensoren.

* aapneServo(): Denne funksjonen åpner servoen ved å sette den i en posisjon på 90 grader. Den tar imot nåværende tid som argument, og oppdaterer variabler som holder styr på tidspunktet for servobevegelsen og om servoen er åpen eller ikke.

* lukkServo(): Denne funksjonen lukker servoen ved å sette den i en posisjon på 0 grader. Den tar imot nåværende tid som argument, og sjekker om servoen har vært åpen i minst 3 sekunder før den lukker den.

* oppdagetSoppel(): Denne funksjonen håndterer tilfeller der søppel er detektert av en av ultralydssensorene. Den aktiverer en lyd- og lysvarsling ved å endre tilstandene til lysdiodene og produsere en lyd hvert 2,5 sekund for å varsle om tilstedeværelsen av søppel.

* ikkeNokSoppel(): Denne funksjonen håndterer tilfeller der det ikke er nok søppel til å utløse varsling. Den sørger for at det ikke spilles noen lyd, og at lysindikatoren forblir grønn for å indikere normal drift.

* skrivUtAvstand(): Denne funksjonen brukes for debugging-formål. 

* microsecondsToCentimeters(): Denne funksjonen konverterer tidsmålinger fra mikrosekunder til centimeter basert på hastigheten til ultralydssignalene. Den tar imot en tidsmåling i mikrosekunder som argument og returnerer avstanden i centimeter.

* lukkServo(): Denne funksjonen brukes i setup() for å sikre at servoen starter i en lukket posisjon.

---
