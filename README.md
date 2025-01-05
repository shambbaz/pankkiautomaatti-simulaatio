# Pankkiautomaattisimulaatio

Tämä projekti on yksinkertainen pankkiautomaattisimulaatio, joka on toteutettu osana Ohjelmointi 1 -kurssia. Projektin tavoitteena oli oppia ohjelmoinnin perusperiaatteita, tiedostojen käsittelyä sekä syötteiden validointia

## Projektin sisältö

Pankkiautomaattiohjelma simuloi oikean pankkiautomaatin toimintaa seuraavilla ominaisuuksilla:
- PIN-koodin tarkistus
- Tilin saldon tarkistus
- Rahan nostaminen (määriteltyjen ehtojen mukaisesti)
- Rahan tallettaminen
- Saldo tallennetaan ja päivitetään tiedostoon ohjelman lopetuksen yhteydessä.

Ohjelma käsittelee tiedostopohjaisia tili- ja saldotietoja ja toimii komentorivikäyttöliittymän avulla.

## Tekninen toteutus

Ohjelma on toteutettu **C-kielellä**, ja projektin kehityksen yhteydessä on hyödynnetty **GitHub Actions** -pohjaista CI/CD-pipelineä, joka sisältää:
- **Continuous Integration (CI):** Ohjelman kääntäminen ja yksikkötestien ajaminen automatisoidusti.
- **Continuous Deployment (CD):** Uuden version julkaiseminen automaattisesti GitHub Releases -välilehdelle.

Pipeline suorittaa seuraavat vaiheet:
1. Koodin kääntäminen (`gcc`).
2. Testien suorittaminen Python-skriptillä.
3. Testitulosten tallentaminen (artifact).
4. Uuden version julkaiseminen GitHub Releases -välilehdelle (mukana ohjelma.exe).

## Projektin rakenne

Seuraavat tiedostot kuuluvat projektiin:
- **`main.c`** - Pääohjelma pankkiautomaattisovellukselle.
- **`12345.tili`** - Testitiedosto tilinumeroille, PIN-koodeille ja saldoille.
- **`run_tests.py`** - Python-skripti testien automatisoimiseksi.
- **`.github/workflows/ci.yml`** - CI/CD-pipeline GitHub Actions -työnkulkua varten.
- **`README.md`** - Projektin dokumentaatio.
- **`testit.txt`** - Testitulosten tallennustiedosto.

## Testaus

Ohjelman testaamiseksi on luotu automatisoitu testausjärjestelmä Python-skriptillä. Skripti kattaa seuraavat skenaariot:
- Normaali käyttö, kuten PIN-koodin syöttö, saldon tarkistus, talletus ja nosto.
- Poikkeustilanteet, kuten virheellinen PIN, negatiiviset summat ja virheelliset syötteet.

Testitulokset tallennetaan tiedostoon **testit.txt**.

## CI/CD-prosessi

Pipeline on määritelty tiedostossa **`.github/workflows/ci.yml`**, ja se suorittaa:
- Ohjelman kääntämisen ja testien ajamisen jokaisen commitin yhteydessä.
- Uuden version julkaisun GitHub Releases -välilehdelle, jossa julkaisu sisältää käännetyn ohjelman (`ohjelma.exe`) ja lähdekoodin.

## Kuinka käyttää

1. Lataa projektin tiedostot GitHubista.
2. Käännä ohjelma:
   ```bash
   gcc main.c -o ohjelma.exe

   
