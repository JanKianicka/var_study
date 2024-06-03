# 24.4.2024 som ukončil hĺbkový test a fixovanie importu všetkých
  meraní okrem InSAR. Tento ale nie je v systéme Zosuvy dokončený.
  Bolo potrebné viacero rozšírení a fixov kde sa zdrojový kód líšil od
  vstupných dát. Niekde nefungovali aktualizácie alebo jednoznačné
  kľúče meraní.  Snažil som sa aj optimalizovať zdĺhavé importy
  napr. pre inklinometriu, hladinu podzemnej vody alebo zrážky
  (pomocou optimalizácie vyhľadávania existujúcich záznamov, alebo
  indexov v DB).  Ale len s čiastočným úspechom. Zmeny v indexoch som
  musel vrátiť do pôvodného stavu.

