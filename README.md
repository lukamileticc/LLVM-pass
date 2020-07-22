# ** LLVM-pass **
Seminarski rad iz predmeta Konstrukcija Kompilatora

## Sta su to llvm-prolazi(pass-ovi):
 Postoje prolazi koji vrse analizu i transformaciju, ja sam napisao jedan koji vrsi analizu. Oni se primenjuju na medjureprezentaciji(jezik koji predstavlja sponu
 visokog programskog jezika i masinskog ili asemblerskog jezika koji se izvrsava na masini) kako bi se dobio optimizovaniji(efikasniji) programski kod.
 
Prolaz se nalazi u direkotrijumu InstructionsCounterIR i samo mu ime govori da broji broj instrukcija koje se pojavljuju u svim blokovima
IR-a(load,store,add,mul...).

## Kako ga pokrenuti: 
  Prvo je potrebno bildovati LLVM ------- http://www.cs.utexas.edu/~pingali/CS380C/2019/assignments/llvm-guide.html
  Zatim je potrebno napraviti direkotrijum koji ima fajlove prolaza : InstructionsCounterIR folder
  i njega ubaciti u llvm/lib/transforms/ folder jer se u to folderu nalaze prolazi LLVM-a...
  Nakon toga u istom tom folderu postoji fajl CMakeLists.txt gde potrebno dodati liniju add_subdirectory(#ime vaseg foldera u kojem se nalzai prolaz)
  i potrebno je opet se pozicionirati u llvm/build direkotriju i upotrebiti opciju : 
  
  ninja ---- kako bismo dobili .so fajl naseg prolaza kojeg cemo kasnije pozvati 
  
  Kada smo to uradili potrebno je prevesti nas program na .ll format
## Kako dobiti .ll fajl: 
U folderu c_konacni_prevodilac su fajlovi koji predstavljaju prevodilac za neki jezik koji lici na pascal:

pozicionirati se u taj direktorijum i ukucati komandu: make

Napravice se izvrsni fajl koji predstavlja prevodilac

Takodje u tom direktorijumu postoje test primeri: tes1 test2 test3 i test4

Kako dobiti kodove u .ll fomatu koji predstavljaju IR(Intermediate representation) LLVM-a:

./prevodilac < test1 > test1.ll

## Kako pokrenuti prolaz:
Kada imamo kodove na IR jeziku potrebno je pozvati prolaz:
opt -load /home/luka/llvm/build/lib/LLVMInstructionsCounterIR.so test1.ll


## Clanovi tima:
  Luka Miletic 91/2017
