# 🚀 Softadastra C++ Backend

This repository contains the C++ backend services for the **Softadastra** platform.  
It is built for high performance, modularity, and real-world scalability across categories, catalogue, payments, and more.

---

## 📦 Project Structure

softadastra_cpp_api/
├── CMakeLists.txt # Root CMake configuration
├── Crow/ # Crow HTTP framework (header-only)
├── include/ # All shared public headers
│ ├── utils/ # Utilities (Logger, EnvLoader, etc.)
│ ├── tools/ # Image processing and helpers
│ ├── payments/ # Payment interfaces and models
│ ├── catalogue/ # ECS entities and systems
│ └── categories/ # Categories service and routes
├── src/ # Module implementations
│ ├── utils/ # Logger, EnvLoader, etc.
│ ├── tools/ # Image compression, OpenCV tools
│ ├── payments/ # Payment API, controllers, services
│ ├── catalogue/ # Catalogue logic, ECS
│ ├── categories/ # Category routes and repository
│ └── main.cpp # Application entry point
└── config/
└── data/
└── leaf_categories.json # Local JSON category data

---

## 🧱 Dependencies

| Library         | Purpose                                   |
|-----------------|-------------------------------------------|
| Crow            | REST API framework                        |
| OpenSSL         | Secure hashing, encryption, SSL support   |
| SQLite3         | Lightweight embedded database (optional)  |
| MySQL Connector | Persistent database (products, payments)  |
| OpenCV          | Image processing and compression tools    |
| nlohmann/json   | Modern JSON parsing                       |
| GoogleTest      | Unit testing framework                    |

---

## 🛠 Build Instructions

### 1. Clone the repository

```bash
git clone https://github.com/softadastra-group/softadastra_cpp_api.git
cd softadastra_cpp_api

2. Create the build directory and configure CMake

mkdir -p build && cd build
cmake .. -DENABLE_SANITIZERS=ON -DENABLE_OPTIMIZATION=OFF
You can enable -DENABLE_OPTIMIZATION=ON for production-ready builds.

3. Build the project

make -j$(nproc)

4. Run the application

./bin/Softadastra

🌍 Environment Configuration
Create a .env file at the root level with the following variables:

CATEGORY_JSON_PATH=../config/data/leaf_categories.json

This allows the app to load static resources such as category data using environment-based paths.

🔌 API Endpoints (Crow)
Method	Route	Description
GET	/api/categories/leaf	List leaf-level product categories
...	(more coming soon)	Payments, products, vendors...

All endpoints include automatic CORS headers and return proper JSON responses.

🧪 Testing (Optional)
If enabled via BUILD_TESTS=ON in CMake:

cd build
ctest

👥 Contributing
Follow the C++17 standard

Document your modules and APIs

Keep routes isolated per domain (payments, catalogue, etc.)

Respect modularity: only import what you need

🧠 Future Modules
inventory: Stock & warehouse tracking

shipping: Integration with delivery partners

vendors: Marketplace account management

ai: Recommendation engine, image classification

🏁 License
This project is proprietary and maintained by Softadastra Group.

---

Would you like me to generate a short `CONTRIBUTING.md` next, or a `Makefile` wrapper for common tasks like `build`, `test`, `run`?




