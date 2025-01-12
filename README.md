# Pankkiautomaattisimulaatio

Tämä projekti on yksinkertainen pankkiautomaattisimulaatio, joka on toteutettu osana Ohjelmointi 1 -kurssia. Projektin tavoitteena oli oppia ohjelmoinnin perusperiaatteita, tiedostojen käsittelyä, syötteiden validointia ja modernien REST API -ratkaisujen käyttöä.

## Projektin sisältö

Pankkiautomaattiohjelma simuloi oikean pankkiautomaatin toimintaa seuraavilla ominaisuuksilla:
- PIN-koodin tarkistus
- Tilin saldon tarkistus
- Rahan nostaminen (määriteltyjen ehtojen mukaisesti)
- Rahan tallettaminen
- Reaaliaikainen tiedonkäsittely REST API:n kautta
- Saldo tallennetaan ja päivitetään tiedostoon tai API:lle ohjelman aikana.

Ohjelma käsittelee REST API -pohjaisia tili- ja saldotietoja ja toimii komentorivikäyttöliittymän avulla.

## REST API

Projektissa lisättiin Flask-pohjainen REST API, joka tarjoaa seuraavat reitit:
- **`/api/balance`** (POST): Tarkistaa tilin saldon syötetyllä PIN-koodilla.
- **`/api/withdraw`** (POST): Nostaa rahaa tililtä, jos saldo riittää.
- **`/api/deposit`** (POST): Tallettaa rahaa tilille.

REST API mahdollistaa reaaliaikaisen tiedonkäsittelyn pankkiautomaattisovelluksessa ja eriyttää tietojen hallinnan sovelluksen logiikasta.

## Tekninen toteutus

Ohjelma on toteutettu **C-kielellä**, ja siihen on integroitu Flask REST API. Projekti hyödyntää myös **GitHub Actions** -pohjaista CI/CD-pipelineä, joka sisältää:
- **Continuous Integration (CI):** Ohjelman kääntäminen ja yksikkötestien ajaminen automatisoidusti.
- **Continuous Deployment (CD):** Uuden version julkaiseminen automaattisesti GitHub Releases -välilehdelle.

### REST API -teknologiat
- **Flask**: Kevyt Python-websovelluskehys REST API:n toteuttamiseen.
- **libcurl**: HTTP-pyyntöjen toteuttamiseen C-ohjelmasta käsin.

Pipeline suorittaa seuraavat vaiheet:
1. Koodin kääntäminen (`gcc`).
2. Testien suorittaminen Python-skriptillä.
3. Testitulosten tallentaminen (artifact).
4. Uuden version julkaiseminen GitHub Releases -välilehdelle (mukana ohjelma.exe).

## Projektin rakenne

Seuraavat tiedostot kuuluvat projektiin:
- **`main.c`** - Pääohjelma pankkiautomaattisovellukselle. Sisältää REST API:n integraation.
- **`flask_api/app.py`** - Flask REST API -kooditiedosto pankkiautomaattisovellusta varten.
- **`12345.tili`** - Testitiedosto tilinumeroille, PIN-koodeille ja saldoille.
- **`run_tests.py`** - Python-skripti testien automatisoimiseksi.
- **`.github/workflows/ci.yml`** - CI/CD-pipeline GitHub Actions -työnkulkua varten.
- **`README.md`** - Projektin dokumentaatio.
- **`testit.txt`** - Testitulosten tallennustiedosto.

## Testaus

Ohjelman testaamiseksi on luotu automatisoitu testausjärjestelmä Python-skriptillä sekä Postmanilla Flask REST API:n testaamiseksi. Skripti ja manuaalinen testaus kattaa seuraavat skenaariot:
- Normaali käyttö, kuten PIN-koodin syöttö, saldon tarkistus, talletus ja nosto.
- Poikkeustilanteet, kuten virheellinen PIN, negatiiviset summat ja virheelliset syötteet.
- REST API:n virheiden ja onnistuneiden pyyntöjen validointi.

Testitulokset tallennetaan tiedostoon **testit.txt**.

## CI/CD-prosessi

Pipeline on määritelty tiedostossa **`.github/workflows/ci.yml`**, ja se suorittaa:
- Ohjelman kääntämisen ja testien ajamisen jokaisen commitin yhteydessä.
- Uuden version julkaisun GitHub Releases -välilehdelle, jossa julkaisu sisältää käännetyn ohjelman (`ohjelma.exe`) ja lähdekoodin.

## Kuinka käyttää

1. Lataa projektin tiedostot GitHubista.
2. Käynnistä Flask REST API:
   ```bash
   cd flask_api
   python app.py
