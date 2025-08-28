# SAYN ATM System v2.0 💳🏦
**SAYN ATM System — Advanced Electronic Banking System** (elektron bankçılıq sistemi) C dilində yazılmışdır.  
Sistem həm **Windows**, həm də **Linux/macOS** əməliyyat sistemlərində işləyir və real **ATM funksiyalarını simulyasiya edir**.

---

## ✨ Xüsusiyyətlər
- ✅ Çoxdilli dəstək (Azərbaycan / İngilis)  
- ✅ Cross-platform uyğunluq (Windows / Linux)  
- ✅ Təhlükəsizlik protokolları (PIN yoxlaması, cəhd limiti)  
- ✅ Əməliyyat tarixçəsi sistemi  
- ✅ Gündəlik çıxarış limiti  
- ✅ PIN dəyişmə funksiyası  
- ✅ Rəngli terminal interfeysi  
- ✅ Input validation & error handling  

---

## 📂 Layihə Strukturu
├── atm.c # Əsas proqram faylı
├── README.md # Layihə haqqında məlumat
└── LICENSE # MIT lisenziyası


---

## ⚙️ Qurulum və İşlətmə

### 🔹 Windows
1. [MinGW](http://mingw-w64.org) və ya GCC quraşdır.  
2. Kodu kompilyasiya et:
   ```bash
   gcc atm.c -o atm.exe


Proqramı işə sal:

atm.exe

🔹 Linux / macOS

GCC kompilyatorunun quraşdırıldığından əmin ol:

sudo apt update && sudo apt install build-essential -y


Kodu kompilyasiya et:

gcc atm.c -o atm


Proqramı işə sal:

./atm

🖥️ İstifadəçi Menyusu
+----------------------------------------------+
|                @ ƏSAS MENYU                  |
+----------------------------------------------+
|  1 -> Nağdlaşdırma (Pul Çıxarma)             |
|  2 -> Hesaba Məbləğ Əlavə Etmək              |
|  3 -> Cari Balansı Göstərmək                 |
|  4 -> Əməliyyat Tarixçəsi                    |
|  5 -> PIN Kod Dəyişdirmək                    |
|  6 -> Sistemə Çıxış                          |
+----------------------------------------------+

🛡️ Təhlükəsizlik

❌ Maksimum 3 uğursuz PIN cəhdi sonrası kart bloklanır.

❌ PIN kodu 4 rəqəmli olmalıdır (1000-9999 aralığında).

❌ Gündəlik çıxarış limiti: 5000 AZN.

❌ Maksimum əməliyyat: 2000 AZN, minimum isə 10 AZN.

📜 Lisenziya

Bu layihə MIT License ilə yayımlanır.
Daha ətraflı: LICENSE

👨‍💻 Developer Info

Developer: M.Nurlan
📧 Email: nurlanmammadli2@gmail.com

🔗 LinkedIn: linkedin.com/in/nurlan-məmmədli-b6a55b308

📍 Location: Sumqayıt, Azərbaycan
