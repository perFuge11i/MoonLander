# MoonLander

## Beskrivelse
Dette prosjektet er et enkelt moonlander spill laget i C++. Spillet er et eksamensprosjekt som inngår i en 
mappeeksamensvurdering i faget AIS1003 ved NTNU (Norges tekniske og naturvitenskaplige universitet)
Meningen og formålet med spillet var å skaffe oss erfaring innen objektorientert programmering.
Spillet bruker flere klasser for å "simulere" en månelanding, inkludert fysikk, kollisjonsdeteksjon, og brukergrensesnitt. 
Grafikken er håndtert av`threepp` biblioteket. 

## Forutsetninger
- **CLion**: Anbefalt å åpne og kjøre prosjektet med CLion IDE.
- **C++ Standard**: Prosjektet bruker C++20.
- **Krav**:
    - [threepp](https://github.com/markaren/threepp.git) for 3D-grafikk.
    - [imgui](https://github.com/ocornut/imgui.git) for brukergrensesnitt.
    - [Catch2](https://github.com/catchorg/Catch2.git) for testing.

## Installasjon og Oppsett
1. Klon prosjektet fra ditt Git-repository.
2. Åpne prosjektet i CLion (anbefalt).
3. Sørg for at alle nødvendige biblioteker er installert.

## Bygging og Kjøring
1. Bygg prosjektet ved å bruke CLion's byggeverktøy.
2. Kjør prosjektet direkte i CLion, hvor hovedkoden ligger i `main.cpp`.

## Bruk
- Bruk piltastene til å kontrollere romskipet under landing.
- `R`-tasten kan brukes for å tilbakestille spillet.
- Spillet gir en grafisk fremstilling av et månelandskap, hvor spilleren skal lande et romskip.

## Testing
- Testene er skrevet med `catch2` som rammeverk og kan kjøres for validering av logikken i spillet.
- Testene er lokalisert i `test.cpp`.


## Skapere
Per Fugelli Lillefosse og Sebastian Myre.