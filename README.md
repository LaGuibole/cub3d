# 🧱 Cub3D  
*A 42 School project — a raycasting engine in C with textures, minimap and player movement, inspired by Wolfenstein 3D.*

---

## 🚀 Features

- ⛓️ **Custom parsing engine** for `.cub` configuration files  
- 🧭 **Mini-map rendering** with real-time player position and direction  
- 🧱 **Wall textures loading** (XPM format)  
- 🔭 **Raycasting engine** for 3D first-person perspective  
- 🎮 **Smooth player movement** (WASD + arrow keys)  
- 🖼️ **Custom MLX rendering** (no external graphics lib)

---

## 🛠️ Installation & Launch

```bash
make
./cub3d maps/map.cub
```

Dependencies:  
- `mlx` (included via 42 MLX library)  
- `gcc` (or any standard C compiler)  
- Works on Linux. For macOS, make sure to use the right `mlx` variant.

---

## 🔧 Controls

| Key | Action         |
|-----|----------------|
| W   | Move forward   |
| S   | Move backward  |
| A   | Strafe left    |
| D   | Strafe right   |
| ←   | Rotate left    |
| →   | Rotate right   |
| ESC | Exit game      |

---

## 📁 .cub File Structure

Each `.cub` file contains:

- Texture paths (`NO`, `SO`, `WE`, `EA`)
- Floor/Ceiling RGB or texture
- Map layout (`1` for wall, `0` for space, `NSEW` for spawn)

---

## 👨‍💻 Contributors

### 🔍 Parsing & 🧭 Mini-map  
**Guillaume Philippe**  
- Configuration file parsing  
- Map validation and flood fill  
- Mini-map with tile rendering, player direction and dot

### 🎯 Raycasting Engine  
**Jonas Bastard**  
- Raycasting (DDA)  
- Textured wall projection  
- Camera plane and direction vectors

---



## 📸 Screenshots

<img src="assets/cub.gif"></img>

---

## 📚 Resources

- [Raycasting Tutorial by Lode Vandevenne](https://lodev.org/cgtutor/raycasting.html)  
- [MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx)

---

## 🏁 Status

✅ **Project complete**  
💡 Always open to improvements and extensions!
