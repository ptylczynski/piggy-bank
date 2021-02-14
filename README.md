# piggy-bank
Toy example of C++ File IO system.  
Project emulates piggy for multiple users. COncurency and thread safety not implemented. Manual `.txt` files modifications discouragesd.

## Architecture
- **main** - contains logic of piggy
- **users** - users data with account balance
- `*.piggies` - files contains piggies associated with user
- `*.piggy` - transaction history of piggy

## Compile & Run
```bash
g++ main.cpp -o piggy-bank
./piggy-bank
```
