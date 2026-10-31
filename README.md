# 🧾 BillBuddy – Grocery Store & Restaurant Bill Calculator

A simple billing project. The billing logic is written in **C**, and a clean web interface
(HTML, CSS, JavaScript) lets a shopkeeper or cashier generate bills quickly.

🔗 **Live Demo:** https://billbuddy-docs.vercel.app

## ✨ Features
- Choose **Grocery Store** or **Restaurant**
- Example items for both, **editable prices** and option to **add new items**
- **Counter / Home Delivery** (address + delivery charges)
- **Cash / UPI** payment (UPI Id or Transaction Id)
- Simple **black & white printable bill** with Thank You message
- **Stock Manager** (separate for Grocery and Restaurant)
- **Today’s sales and Last 7 days sales** (separate data for each)
- Up to **2 accounts** per store type
- **Light, Dark and Glass** themes, works on PC and mobile

## 🛠️ Languages Used
| Language | Used for |
|---|---|
| C | Core billing logic (console version) |
| HTML | Web page structure |
| CSS | Design, themes, animations |
| JavaScript | Web interface logic (same formula as the C code) |

## 📁 Repository Structure
```
BillBuddy/
├── src/
│   └── main.c        # C program (console version)
├── docs/
│   └── index.html    # Web interface (hosted with GitHub Pages)
├── screenshots/      # Project screenshots
├── README.md
└── .gitignore
```

## ▶️ Run the C program
```bash
gcc src/main.c -o billbuddy
./billbuddy          # Windows: billbuddy.exe
```

## 🌐 Run the web version
Open the Live Demo link, or open `docs/index.html` in any browser.

## 🧮 Billing formula
`Total = Subtotal + (Subtotal × GST% / 100) + Delivery charge`

## 👥 Team
Made with ❤️ by **Team Coder’s Syndicate**
Bugs or issues? Email: sohampednekar2710@gmail.com
