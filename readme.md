## UPDATE: reverse engineering is now complete. See the arduino sketch here: https://github.com/njanik/hayward-pool-heater-mqtt ##


----


Les fichiers avec l'extension logicdata sont des captures faites avec un petit logic analyser acheté 8$ sur ebay.
Vous pouvez réouvrir les captures avec le logiciel de salae (https://www.saleae.com/downloads/)

Les données sont aussi exporté en CSV pour pouvoir etre parsé plus facilement par des scripts.

-------------

Conditions initiales générales (pour toutes les captures):
Mode: Heat
Temp out: 28C
Temp prog: 27C

**file no-touch:**  
*Conditions initiales: ON*  
- (rien modifié)

**file on-to-off:**  
*Conditions initiales: ON*
- @60s => set OFF

**file A:**  
*Conditions initiales: OFF*
- @20s => set ON
- @35s => set OFF
- @50s => set ON
- @1'30s => set OFF
- @1'48s => set ON

**file B:**

*Conditions initiales: ON*
- @32s => de 27C à 30C (Je n'ai pas noté quand le fan c'est mis en fct...)
- @1'29s => de 30 à 27C
- @2'18s => de 27 à 30C (le fan c'est mis en fct à 2'31)

**file C:**

*Conditions initiales: ON*
- @25s => set temp à 30C (le fan c'est mis en fonction a 38s)
- @1'03s => set temp à 27C (le fan a stoppé a 1'15s)
- @1'30s => set OFF
- @1'45s => set ON
- @2'20s => set OFF
- @2'30s => set ON

*Les timings sont approximatif à 1 ou 2 secondes près...*



