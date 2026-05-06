# Snake en TTGO T-Display v1.1

Juego clásico Snake programado para la placa TTGO T-Display v1.1 (ESP32) con pantalla integrada. La serpiente se mueve automáticamente y se controla con los botones físicos de la placa.

Controles
- Botón GPIO0 → Girar a la izquierda
- Botón GPIO35 → Girar a la derecha
- La serpiente avanza automáticamente.
- Si choca contra los bordes o contra su propio cuerpo, aparece la pantalla de Game Over.
- Para reiniciar, mantén presionado cualquiera de los botones.

Pantallas
- Inicio:
"Presiona START"
- Derrota:
"Perdiste malo qlo"

Requisitos
- Placa TTGO T-Display v1.1 (ESP32)
- Librería TFT_eSPI configurada para TTGO T-Display
- Arduino IDE o PlatformIO para cargar el código

## Instalación
1. Clona este repositorio:
git clone https://github.com/rvalvev/ttgo-snake.git
2. Abre el proyecto en Arduino IDE.
3. Configura la librería TFT_eSPI para TTGO T-Display.
4. Carga el código en tu placa ESP32.
5. a JUGARRR

## Licencia
Este proyecto está bajo la licencia MIT. Puedes usarlo, modificarlo y distribuirlo libremente, siempre dando crédito al autor.

## Autor
Rodrigo Valenzuela Vera
