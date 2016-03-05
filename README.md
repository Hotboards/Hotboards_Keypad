Hotboards_Keypad
=================

Genial libreria de proposito general para leer teclados matriciales con pull-ups externas en las columnas, se puede obtener la ultima tecla presionada, cambiar el tiempo en el que una tecla es poleada, incluso permite presionar mas de una tecla al mismo tiempo Descarga la libreria en formato  [**zip**](https://github.com/Hotboards/Hotboards_Keypad/archive/master.zip), renombra el archivo ( _solo quita el **-master**_ ) e importala a tu Arduino IDE com dice [aqui](http://developer.mbed.org/cookbook/Working-with-Libraries).

NOTE:
----

This library was modified by **Hotboards** to be compatible with the **Hotboards keyboard** board, since the original is intend to work with keypads with pullups on rows.

Keypad library is originaly coded by:

**Authors:**  *Mark Stanley***,** *Alexander Brevig*

This repository is a copy of the code found here [[Arduino Playground]](http://playground.arduino.cc/Code/Keypad).

API
---

**Keypad(char *userKeymap, DigitalInOut *row, DigitalInOut *col, uint8_t numRows, uint8_t numCols)**

Constructor para nuestro teclado. Se puede especificar el valor que tendra cada tecla, asi como el numero de filas y columnas, es importante que coincidan en el mapa de teclas como en los pines.

``` cpp
// definimos el mapa de nuestro teclado
char keys[ 4 ][ 4 ] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
// los pines que conectaran las filas
byte rowPins[ 4 ] = { 5, 4, 3, 2 };
// los pines que conectaran las columnas
byte colPins[ 4 ] = { 9, 8, 7, 6 };
// creamos nuestro teclado
Keypad kpd( makeKeymap( keys ), rowPins, colPins, 4, 4 );
```

**char getKey( void )**

Regresa la ultima tecla presionada. El valor de la tecla sera aquel definido por el usuario en el mapa de teclas (keymap), es necesario llamar esta funcion continuamente ya que posee internamente codigo antirebotes.

``` cpp
char key = keypad.getKey( );

if( key ){
  // do something with key
}
```

**bool getKeys( void )**

Actualiza la lista de teclas activas ( _arreglo key_ )  y ademas regresa un verdadero si una tecla cambio su estado. Es necesario buscar la tecla que cambio su estado en el arreglo **key**

``` cpp
// preguntamos si una tecla a cambiado su estado
if( kpd.getKeys( ) ){
  // buscamos la tecla que cambio su estado
  for( int i=0 ; i<LIST_MAX ; i++ ){
    if( kpd.key[ i ].stateChanged ){
      // aqui esta la tecla =)
      chat = kpd.key[ i ].kchar;
  }
}
```

**void addEventListener( void (*listener)(char) )**

Establece una funcion que se llamara automaticamente cada que una tecla cambie su estado. Es necesario que la funcion `geyKeys` se siga llamando continuamente, pues es dentro de esta funcion que se mandara llamar la funcion que establescamos.

``` cpp
void setup(void){
    // ete es un ejemplo, por practicidad la creacion del teclado no la colocamos
    // seteamos la funcion keypadEvent
    kpd.addEventListener( keypadEvent );
}

void loop( void ){
    kpd.getKeys( );
}

void keypadEvent( char key )
{
    // aqui procesamos el cambio de estado de la tecla
}
```

**void setDebounceTime( uint )**

Establece un nuevo tiempo de debounce. Por default el teclado se lee cada 10ms, con esto se evitan los rebotes, esta funcion se usa para modificar este valor.

``` cpp
// Cambia el tiempo de debounce a 20ms
kpd.setDebounceTime( 20 );
```

**void setHoldTime( uint )**

Establece un nuevo tiempo de "hold" es decir el tiempo quen un boton necesita durar presionado para ser considerado en el estado de **PRESSED**. el valor por default es 500ms.

``` cpp
// Cambia el tiempo de hold a 250ms
kpd.setHoldTime( 250 );
```

Ejemplos
--------

- [Leemos una sola tecla presionada de teclado](https://github.com/Hotboards/Hotboards_Keypad/blob/master/examples/HelloKeypad/HelloKeypad.ino)
- [Cambiamos el tiempo necesario para detectar una tecla](https://github.com/Hotboards/Hotboards_Keypad/blob/master/examples/LoopCounter/LoopCounter.ino)
- [Leemos mas de una tecla presionada](https://github.com/Hotboards/Hotboards_Keypad/blob/master/examples/MultiKey/MultiKey.ino)
- [Como llamar funciones cuando una tecla cambia de estado](https://github.com/Hotboards/Hotboards_Keypad/blob/master/examples/EventKeypad/EventKeypad.ino)
- [Cambiando el mapa de nuestro teclado](https://github.com/Hotboards/Hotboards_Keypad/blob/master/examples/DynamicKeypad/DynamicKeypad.ino)
