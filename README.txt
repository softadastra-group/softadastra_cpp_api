# ⚙️ Softadastra – C++ Backend API

**High-performance backend for the Softadastra platform**, built entirely in **modern C++17**.  
It uses [Crow](https://github.com/CrowCpp/Crow) as the HTTP framework, **Boost.Beast** for low-level networking, and integrates with **OpenSSL**, **SQLite3**, and **MySQL C++ Connector** for security and data persistence.

---

## 🧱 Project Overview

This repository contains the full backend API of **Softadastra**, optimized for speed, modularity, and scalability.

🔹 Key Features:

- RESTful APIs for sellers, products, orders, payments, chat, and notifications  
- Dual database support: SQLite3 (local dev) and MySQL (production)  
- Secure communication via OpenSSL  
- Modular architecture with isolated services  
- Full test suite using GoogleTest

---

## 📁 Project Structure

├── CMakeLists.txt # Main build configuration
├── include/ # Shared headers
├── src/ # Core source code (routes, services, handlers)
├── Crow/ # Crow HTTP framework (optional local copy)
├── lib/ # Custom or third-party libraries
├── config/ # Configuration files (JSON, ENV)
├── test/ # Functional test scenarios
├── unittests/ # Unit tests with GoogleTest
├── tools/ # Developer tools and utilities
├── build/ # CMake build output (ignored in Git)
└── README.md # Project documentation

---

## 🛠️ Prerequisites

You must have the following installed:

- CMake ≥ 3.14  
- A C++17-compatible compiler (GCC or Clang)  
- OpenSSL  
- SQLite3  
- MySQL Connector C++  
- Git

### ▶️ Install on Ubuntu/Debian:

```bash
sudo apt update
sudo apt install build-essential cmake libssl-dev libsqlite3-dev libmysqlcppconn-dev

⚙️ Building the Project
From the root of this repository:

mkdir -p build
cd build
cmake .. -DENABLE_SANITIZERS=ON -DBUILD_TESTS=ON
make -j$(nproc)

The compiled binary will be located at:
./build/bin/Softadastra

🚀 Running the Backend
To run the API server:

cd build
ctest --output-on-failure

By default, it listens on http://localhost:8080.

🧪 Testing
Run unit and functional tests using ctest:

cd build
ctest --output-on-failure

./unittests/test_suite

📡 API Example
🔹 GET Products of a Seller

GET /api/seller/123/products HTTP/1.1
Host: localhost:8080
Accept: application/json

🔹POST Create a Product

POST /api/product/create HTTP/1.1
Host: localhost:8080
Content-Type: application/json

{
  "name": "Shirt",
  "price": 24.99,
  "category": "Men",
  "seller_id": 123
}


🤝 Contribution Guidelines
Please follow the internal coding standards (see CONTRIBUTING.md if available):

Code must compile with the flags and options defined in CMakeLists.txt

Write clean, readable, and tested code

Each feature must include its corresponding unit tests if applicable

📄 License
© 2025 Softadastra Group – All Rights Reserved
This repository is proprietary. Contact us for licensing or integration inquiries.

🌍 About Softadastra
Softadastra is a modern e-commerce marketplace connecting Uganda and the Democratic Republic of Congo, built to reduce friction in cross-border trade and empower local entrepreneurs.

🔗 https://softadastra.com

---

Souhaites-tu que je te le génère dans un fichier `README.md` prêt à copier/coller ou te l’envoyer en fichier joint ?
