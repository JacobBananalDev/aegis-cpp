# 🛡️ Aegis C++

Aegis is a modern C++ security engine designed to explore JWT validation, cryptographic primitives, and secure system architecture.

This project focuses on understanding authentication mechanics at a low level while maintaining clean, modular CMake-based design.

---

# 🚀 Current Features (v1)

- ✅ JWT structural validation (`header.payload.signature`)
- ✅ Base64URL decoding
- ✅ JSON payload parsing using `nlohmann/json`
- ✅ Issuer (`iss`) validation
- ✅ Expiration (`exp`) validation
- ✅ Clean modular project structure
- ✅ CMake-based build system (C++20)

---

# 🔐 Security Notes

Aegis currently validates:

- Token format
- Issuer consistency
- Expiration timestamp

⚠️ Signature verification (HMAC SHA256) is planned for the next phase.

Production systems should always rely on hardened JWT libraries and cryptographic primitives to avoid implementation vulnerabilities.

---

# 🏗️ Architecture

```

aegis-cpp/
│
├── CMakeLists.txt
├── README.md
├── src/
│   ├── main.cpp
│   ├── jwt/
│   │   ├── JwtUtils.h
│   │   └── JwtUtils.cpp
│   └── external/
│       └── json.hpp

````

Design principles:

- Separation of concerns
- Modular JWT utilities
- Minimal entry-point logic
- Cross-platform build configuration via CMake

---

# 🛠️ Build Requirements

- Windows 10/11
- Visual Studio 2022
- CMake 3.20+
- C++20 compatible compiler

---

# 🔧 Build Instructions

Clone the repository:

```bash
git clone https://github.com/JacobBananalDev/aegis-cpp.git
cd aegis-cpp
````

Open the folder in **Visual Studio 2022** using:

```
File → Open → Folder
```

Visual Studio will automatically configure the CMake project.

Build and run the `aegis` target.

---

# ▶️ Usage

Run the executable with a JWT token:

```bash
aegis.exe <jwt_token>
```

Example test token:

```
eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJUZXN0SXNzdWVyIiwiZXhwIjozMDAwMDAwMDAwfQ.dummysignature
```

Example output:

```
JWT structure valid.
Decoded Header:
{"alg":"HS256","typ":"JWT"}

Decoded Payload:
{"iss":"TestIssuer","exp":3000000000}

JWT claim validation passed.
```

---

# 🗺️ Roadmap

Planned improvements:

* 🔒 HMAC SHA256 signature verification (OpenSSL)
* 🎯 Algorithm enforcement (`alg` validation)
* 👥 Audience (`aud`) validation
* 🧑‍💼 Role-based claim enforcement (RBAC)
* 🐳 Docker containerization
* 🧪 CI-integrated static analysis
* 📦 vcpkg-based dependency management

---

# 🎓 Purpose

Aegis is a learning and portfolio project intended to demonstrate:

* Systems-level C++ development
* Secure token validation workflows
* JSON parsing and claim enforcement
* Modular architecture design
* Modern CMake configuration

The goal is to bridge high-level authentication concepts (commonly abstracted in frameworks like .NET) with low-level cryptographic understanding in C++.

---

# ⚖️ Disclaimer

This project is for educational and portfolio purposes.
It is not intended to replace production-grade authentication libraries.

Always use well-maintained, security-audited libraries in production systems.
