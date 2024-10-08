# Manejo de puertos
Existen dos métodos que nos van a ayudar a realizar el manejo de puertos.

## Apertura de puerto
Este método permite abrir el puerto serial de comunicación para poder enviar las instrucciones al PoS.
Para realizar la apertura el puerto usamos el método **vpiOpenPort**.
````c
Int vpiOpenPort (comParams_t* params)
````
Recibe una estructura como parametro, comParams_t:
````c
typedef struct COM_PARAMS{
	LPSTR com;          // Nombre del puerto. Ej: "COM1", "COM2", etc.
	WORD  baudRate;     // Velocidad de transmición: 19200
	WORD byteSize;      // Largo del byte: 8
	char  parity;       // Paridad: 'N'
	WORD  stopBits;     // Bits de parada: 1
}comParams_t;
````
Cumpliendo con las siguientes caracteristicas:
|       Campo       |   Largo Máximo    |
|:-----------------:|:-----------------:|
|   com          	|       5          	|
|   baudRate   		|       5          |  
|   byteSize 		|       1          |
|   parity      	|       1           |
|   stopBits        |       1           |

Para una ejecución exitosa el puerto debe estar cerrado y disponible.

## Cierre de puerto
Este método realiza el cierre del puerto y lo deja libre para otras aplicaciones.
Para cerrar el puerto empleamos el método **vpiClosePort**
````c
Int vpiClosePort()
````
El puerto debe estar abierto para que la ejecución sea exitosa. Luego de ejecutar este comando, si se desea establecer nuevamente la comunicación con el PoS, se debe realizar la apertura del puerto.
## Posibles Retorno para ambos métodos
Los posibles valores de retorno de los métodos son los siguientes:
````
VPI_OK
VPI_FAIL
````
En la sección [códigos de respuesta](../Libreria/codigosRespuesta.md) de la librería de integración se pueden ver la tabla de valores para estas respuestas

---
#### Otros enlaces
- [Principal](../README.md).
- [Manejo de puertos](./Puertos.md)
- [Prueba de comunicación](./ComTest.md)
- [Venta](./Venta.md).
- [Venta + Extracción](./Venta+Extracción.md).
- [Venta con QR](./VentaQR.md) + pago con transferencias.
- [Anulacion](./Anulacion.md)
- [Cierre de lote](./cierreLote.md).
- [Devolución](./Devolucion.md).
- [Consulta de último cierre de lote](./consultaCierre.md).
- [Consulta de última transacción](./consultaUltTransaccion.md).
- [Consulta de tarjetas](./consultaTarjetas.md) disponibles para operar.
- [Consulta de planes](./consultaPlanes.md) a aplicar por tarjeta.