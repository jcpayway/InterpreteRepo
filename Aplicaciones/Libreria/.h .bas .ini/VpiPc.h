#pragma once

#ifndef _VPIPC_H_
#define _VPIPC_H_
/**
* VpiPc.h
* Contiene la declaraci�n de la sunciones que implementan la comunicaci�n
* utilizando el protocolo IngStore, entre una PC y un POS Ingenico con la
* aplicaci�n de VISA con POS Integrado.
*/

#include "ClassicCommandCodes.h"
#include "../IngStoreStaticLib/POSResponseCodes.h"

/*------------------------------CONSTANTES------------------------------*/

/**
* Codigos de retorno de las funciones
*/
#define VPI_OK				0	// Operacion exitosa
#define VPI_MORE_REC		1	// Operacion exitosa, pero faltan registros

#define VPI_FAIL			11	// El comando no pudo ser enviado
#define VPI_TIMEOUT_EXP		12	// Tiempo de espera agotado.

#define VPI_INVALID_ISSUER	101	// El c�digo de tarjeta no existe.
#define VPI_INVALID_TICKET  102 // El n�mero de cup�n no existe.
#define VPI_INVALID_PLAN	103 // El c�digo de plan no existe.
#define VPI_INVALID_INDEX	104	// No existe el indice
#define VPI_EMPTY_BATCH		105	// El lote del POS se encuentra vac�o.

#define VPI_TRX_CANCELED	201 // Transacci�n cancelada por el usuario.
#define VPI_DIF_CARD		202 // La tarjeta deslizada por el usuario no coincide con la pedida.
#define VPI_INVALID_CARD	203 // La tarjeta deslizada no es v�lida.
#define VPI_EXPIRED_CARD	204 // La tarjeta deslizada est� vencida.
#define VPI_INVALID_TRX		205 // La transacci�n original no existe. 

#define VPI_ERR_COM			301 // El POS no pudo comunicarse con el host.
#define VPI_ERR_PRINT		302 // El POS no pudo imprimir el ticket.

#define VPI_INVALID_IN_CMD		901 // Nombre del comando inexistente.
#define VPI_INVALID_IN_PARAM	902 // Formato de alg�n par�metro de entrada no es correcto.
#define VPI_INVALID_OUT_CMD		903 // El comando enviado por 

#define VPI_GENERAL_FAIL		909 // Error general en la operaci�n.

/**
* Codigos de las operaciones (LEGACY)
*/
#define VPI_PURCHASE		1	// Venta
#define VPI_VOID			2	// Anulaci�n de venta
#define VPI_REFUND			3	// Devoluci�n
#define VPI_REFUND_VOID		4	// Anulaci�n de devoluci�n

/**
* Timeouts
*/
#define VPI_TIMEOUT_STD		3000	// Timeout m�nimo 3 segundos
#define VPI_TIMEOUT_HIG		60000	// Timeout alto 60 segundos
#define VPI_TIMEOUT_MED		30000	// Timeout medio 30 segundos
#define VPI_TIMEOUT_LOW		10000	// Timeout bajo 10 segundos

/*------------------------------STRUCTS------------------------------*/

/**
* Par�metros de configuraci�n del puerto serial.
*/
typedef struct COM_PARAMS{

	LPSTR com;			// Nombre del puerto. Ej: "COM1", "COM2", etc.
	WORD  baudRate;		// Velocidad de transmici�n: Ej: 19200
	WORD byteSize;		// Largo del byte. Ej: 7, 8
	char  parity;		// Paridad. Ej: 'N' ninguna, 'E' par, 'O' impar
	WORD  stopBits;		// Bits de parada. Ej: 1, 2
	
}comParams_t;

/**
* Parametros de entrada para la funcion de Venta
*/
typedef struct PURCHASE_IN{

	LPSTR amount;			// Monto *100  
	LPSTR receiptNumber;	// N�mero de factura  
	LPSTR instalmentCount;	// Cant. de cuotas  
	LPSTR issuerCode;		// C�digo de tarjeta  
	LPSTR planCode;			// C�digo de plan  
	LPSTR tip;				// Propina *100
	LPSTR merchantCode;		// C�digo de comercio a utilizar
	LPSTR merchantName;		// Razon social del comercio
	LPSTR cuit;				// CUIT del comercio
	char  linemode;			// transaccion Online(1) o Offline(0) 

}vpiPurchaseIn_t;

/**
* Parametros de entrada para la funcion de Eliminar Reverso
*/
typedef struct DELETEREV_IN {

	LPSTR amount;			// Monto *100  	
	LPSTR instalmentCount;	// Cant. de cuotas  
	LPSTR issuerCode;		// C�digo de tarjeta  
	LPSTR planCode;			// C�digo de plan  
	LPSTR tip;				// Propina *100
	LPSTR merchantCode;		// C�digo de comercio a utilizar
	LPSTR panFirst6;		// Primeros 6
	LPSTR panLast4;			// Ultimos 4
	LPSTR issuerCodeVRE;	// C�digo de tarjeta VRE

}vpiRevDeleteIn_t;

/**
* Parametros de entrada para la funcion de Venta con nombre grupo
*/
typedef struct PURCHASEGROUP_IN {

	LPSTR amount;			// Monto *100  
	LPSTR receiptNumber;	// N�mero de factura  
	LPSTR instalmentCount;	// Cant. de cuotas  
	LPSTR issuerCode;		// C�digo de tarjeta  
	LPSTR planCode;			// C�digo de plan  
	LPSTR tip;				// Propina *100
	LPSTR groupName;		// Nombre del Grupo a utilizar
	LPSTR merchantName;		// Razon social del comercio
	LPSTR cuit;				// CUIT del comercio
	char  linemode;			// transaccion Online(1) o Offline(0) 

}vpiPurchaseGroupIn_t;


/**
* Parametros de entrada para la funcion de Anulacion y Anulacion de Devolucion
*/
typedef struct VOID_IN{  
	
	LPSTR originalTicket;   // N�mero de cup�n de trx. original  
	LPSTR issuerCode;       // C�digo de tarjeta
	LPSTR merchantName;		// Razon social del comercio
	LPSTR cuit;				// CUIT del comercio

}vpiVoidIn_t;

/**
* Parametros de entrada para la funcion de Devolucion
*/
typedef struct REFUND_IN{  
	
	LPSTR amount;			// Monto *100  
	LPSTR instalmentCount;	// Cant. de cuotas  
	LPSTR issuerCode;		// C�digo de tarjeta  
	LPSTR planCode;			// C�digo de plan  
	LPSTR originalTicket;	// Nro. ticket de la trx. original  
	LPSTR originalDate;		// Fecha de la trx. original
    LPSTR receiptNumber;	// N�mero de factura 
	LPSTR merchantCode;		// C�digo de comercio a utilizar
	LPSTR merchantName;		// Razon social del comercio
	LPSTR cuit;				// CUIT del comercio
	char  linemode;			// transaccion Online(1) o Offline(0) 
}vpiRefundIn_t;

/**
* Parametros de salida para las funciones de Venta, Anulacion y Devolucion
*/
typedef struct TRX_OUT{   
	
	LPSTR hostRespCode;	// C�digo de respuesta del host   
	LPSTR hostMessage;  // Mensaje de respuesta del host   
	LPSTR authCode;     // N�mero de autorizaci�n   
	LPSTR ticketNumber; // N�mero de cup�n   
	LPSTR batchNumber;  // N�mero de lote   
	LPSTR customerName; // Nombre del tarjeta-habiente   
	/* Eldar MOD ---> */
  	LPSTR panFirst6;    // Primeros 6 digitos de la tarjeta
  	/* <--- Eldar MOD */
	LPSTR panLast4;     // Ultimo 4 digitos de la tarjeta   
	LPSTR date;         // Fecha de la transacci�n   
	LPSTR time;         // Hora de la transaccion
	LPSTR terminalID;

}vpiTrxOut_t;


/**
* Parametros de salida para las funciones de Venta con marca de retorno cons codigo de comercio
*/
typedef struct TRXMARK1_OUT {

	LPSTR hostRespCode;	// C�digo de respuesta del host   
	LPSTR hostMessage;  // Mensaje de respuesta del host   
	LPSTR authCode;     // N�mero de autorizaci�n   
	LPSTR ticketNumber; // N�mero de cup�n   
	LPSTR batchNumber;  // N�mero de lote   
	LPSTR customerName; // Nombre del tarjeta-habiente   
	LPSTR panLast4;     // Ultimo 4 digitos de la tarjeta   
	LPSTR panFirst6;    // Primeros 6 digitos de la tarjeta	
	LPSTR date;         // Fecha de la transacci�n   
	LPSTR time;         // Hora de la transaccion
	LPSTR terminalID;	// Numero de Terminal
	LPSTR issuerCode;	// C�digo de tarjeta
	LPSTR merchantCode;	// C�digo de comercio
	LPSTR aipEmv;		// Aip para EMV
	LPSTR appEmv;		// App para EMV
	LPSTR promoMsg;		// Mensaje promocional

}vpiTrxMarkOut1_t;

/**
* Parametros de salida para las funciones de Venta con marca de retorno sin codigo de comercio
*/
typedef struct TRXMARK_OUT {

	LPSTR hostRespCode;	// C�digo de respuesta del host   
	LPSTR hostMessage;  // Mensaje de respuesta del host   
	LPSTR authCode;     // N�mero de autorizaci�n   
	LPSTR ticketNumber; // N�mero de cup�n   
	LPSTR batchNumber;  // N�mero de lote   
	LPSTR customerName; // Nombre del tarjeta-habiente   
	LPSTR panLast4;     // Ultimo 4 digitos de la tarjeta   
	LPSTR panFirst6;    // Primeros 6 digitos de la tarjeta	
	LPSTR date;         // Fecha de la transacci�n   
	LPSTR time;         // Hora de la transaccion
	LPSTR terminalID;	// Numero de Terminal
	LPSTR issuerCode;	// C�digo de tarjeta
	LPSTR aipEmv;		// Aip para EMV
	LPSTR appEmv;		// App para EMV
	LPSTR promoMsg;		// Mensaje promocional

}vpiTrxMarkOut_t;

/**
* Parametros de salida para las funciones de Venta sin borrar reverso
*/
typedef struct TRXREV_OUT {

	LPSTR hostRespCode;	// C�digo de respuesta del host   
	LPSTR hostMessage;  // Mensaje de respuesta del host   
	LPSTR authCode;     // N�mero de autorizaci�n   
	LPSTR ticketNumber; // N�mero de cup�n   
	LPSTR batchNumber;  // N�mero de lote   
	LPSTR customerName; // Nombre del tarjeta-habiente   
	LPSTR panLast4;     // Ultimo 4 digitos de la tarjeta   
	LPSTR panFirst6;    // Primeros 6 digitos de la tarjeta	
	LPSTR date;         // Fecha de la transacci�n   
	LPSTR time;         // Hora de la transaccion
	LPSTR terminalID;	// Numero de Terminal
	LPSTR issuerCode;	// C�digo de tarjeta
	LPSTR aipEmv;		// Aip para EMV
	LPSTR appEmv;		// App para EMV
	LPSTR promoMsg;		// Mensaje promocional

}vpiTrxRevOut_t;

/**
* Parametros de salida para las funciones de Venta con multiples establecimientos
*/
typedef struct TRXGROUP_OUT {

	LPSTR hostRespCode;	// C�digo de respuesta del host   
	LPSTR hostMessage;  // Mensaje de respuesta del host   
	LPSTR authCode;     // N�mero de autorizaci�n   
	LPSTR ticketNumber; // N�mero de cup�n   
	LPSTR batchNumber;  // N�mero de lote   
	LPSTR customerName; // Nombre del tarjeta-habiente   
	LPSTR panLast4;     // Ultimo 4 digitos de la tarjeta   
	LPSTR panFirst6;    // Primeros 6 digitos de la tarjeta	
	LPSTR date;         // Fecha de la transacci�n   
	LPSTR time;         // Hora de la transaccion
	LPSTR terminalID;	// Numero de Terminal
	LPSTR issuerCode;	// C�digo de tarjeta
	LPSTR merchantCode;	// C�digo de comercio
	LPSTR aipEmv;		// Aip para EMV
	LPSTR appEmv;		// App para EMV
	LPSTR promoMsg;		// Mensaje promocional

}vpiTrxGroupOut_t;

/**
* Parametros de salida para las funciones de consulta de credito directo (CCD)
*/
typedef struct CCDMARK_OUT {

	LPSTR hostRespCode;	// C�digo de respuesta del host   
	LPSTR hostMessage;  // Mensaje de respuesta del host   
	LPSTR authCode;     // N�mero de autorizaci�n   
	LPSTR ticketNumber; // N�mero de cup�n   
	LPSTR batchNumber;  // N�mero de lote   
	LPSTR customerName; // Nombre del tarjeta-habiente   
	LPSTR panFirst6;    // Primeros 6 digitos de la tarjeta	
	LPSTR panLast4;     // Ultimo 4 digitos de la tarjeta   
	LPSTR date;         // Fecha de la transacci�n   
	LPSTR time;         // Hora de la transaccion
	LPSTR terminalID;	// Numero de Terminal
	LPSTR issuerCode;	// C�digo de tarjeta
	LPSTR merchantCode;	// C�digo de comercio
	LPSTR aipEmv;		// Aip para EMV
	LPSTR appEmv;		// App para EMV
	LPSTR instCount1;	// Cantidad de cuotas
	LPSTR valueCount1;	// Valor de la Cuota
	LPSTR TNA1;			// TNA (3 enteros y 2 decimales)
	LPSTR instCount2;	// Cantidad de cuotas
	LPSTR valueCount2;	// Valor de la Cuota
	LPSTR TNA2;			// TNA (3 enteros y 2 decimales)
	LPSTR instCount3;	// Cantidad de cuotas
	LPSTR valueCount3;	// Valor de la Cuota
	LPSTR TNA3;			// TNA (3 enteros y 2 decimales)
	LPSTR instCount4;	// Cantidad de cuotas
	LPSTR valueCount4;	// Valor de la Cuota
	LPSTR TNA4;			// TNA (3 enteros y 2 decimales)
	LPSTR instCount5;	// Cantidad de cuotas
	LPSTR valueCount5;	// Valor de la Cuota
	LPSTR TNA5;			// TNA (3 enteros y 2 decimales)
	LPSTR emisorName;	// Nombre del Banco emisor
	LPSTR promoMsg;		// Mensaje promocional

}vpiCcdMarkOut_t;

/**
* Parametros de salida de la funcion de Cierre de lote.
*/
typedef struct BATCHCLOSE_OUT{  

	LPSTR hostRespCode;	// Codigo de respuesta del host  
	LPSTR date;			// Fecha ("DD/MM/AAAA")  
	LPSTR time;			// Hora ("HH:MM:SS")
	LPSTR terminalID;

}vpiBatchCloseOut_t;

/**
* Registro con los totales por tarjeta del Cierre de lote.
*/
typedef struct BATCHCLOSEDATA_OUT{   
	
	WORD index;				// �ndice del registro.   
	LPSTR acquirerCode;		// C�digo de procesador.   
	LPSTR batchNumber;		// N�mero de lote.   
	LPSTR issuerCode;		// C�digo de tarjeta   
	LPSTR purchaseCount;	// Cantidad de ventas.   
	LPSTR purchaseAmount;	// Monto total de ventas.   
	LPSTR voidCount;		// Cantidad anulaciones de venta.   
	LPSTR voidAmount;		// Monto total de anulaciones.   
	LPSTR refundCount;		// Cantidad de devoluciones venta.   
	LPSTR refundAmount;		// Monto total de devoluciones.   
	LPSTR refvoidCount;		// Cantidad anulaciones devoluci�n.   
	LPSTR refvoidAmount;	// Monto total anul. devoluci�n.
	LPSTR date;				// Fecha ("DD/MM/AAAA")  
	LPSTR time;				// Hora ("HH:MM:SS")
	LPSTR terminalID;

}vpiBatchCloseDataOut_t;

/**
* Registro con los totales por tarjeta del Cierre de lote con grupo.
*/
typedef struct BATCHCLOSEDATAGROUP_OUT {

	WORD index;				// �ndice del registro.   
	LPSTR acquirerCode;		// C�digo de procesador.   
	LPSTR batchNumber;		// N�mero de lote.   
	LPSTR groupName;		// Nombre del grupo.
	LPSTR issuerCode;		// C�digo de tarjeta   
	LPSTR purchaseCount;	// Cantidad de ventas.   
	LPSTR purchaseAmount;	// Monto total de ventas.   
	LPSTR voidCount;		// Cantidad anulaciones de venta.   
	LPSTR voidAmount;		// Monto total de anulaciones.   
	LPSTR refundCount;		// Cantidad de devoluciones venta.   
	LPSTR refundAmount;		// Monto total de devoluciones.   
	LPSTR refvoidCount;		// Cantidad anulaciones devoluci�n.   
	LPSTR refvoidAmount;	// Monto total anul. devoluci�n.
	LPSTR date;				// Fecha ("DD/MM/AAAA")  
	LPSTR time;				// Hora ("HH:MM:SS")
	LPSTR terminalID;

}vpiBatchCloseDataGroupOut_t;

/**
* Entrada para IES
*/
typedef struct IES_IN {

	LPSTR issuerCode;     //C�digo de tarjeta   
	LPSTR newReg;	      //Ultimo registro
	LPSTR nameGroup;	  //Nombre del Grupo.
	LPSTR merchant;		  //Numero de establecimiento.

}vpiIesIn_t;

/**
* Retorno para IES
*/
typedef struct IES_OUT {

	WORD index;           //�ndice del registro.
	LPSTR respcode;		  //Codigo de respuesta. 
	LPSTR issuerCode;     //C�digo de tarjeta   
	LPSTR issuerName;     //Nombre de la tarjeta
	LPSTR merchant;		  //Numero de establecimiento.
	LPSTR nameGroup;	  //Nombre del Grupo.
	LPSTR terminalID;	  //Terminal ID.

}vpiIesOut_t;

//ADD 1.18 Marzo 2020
/**
* Entrada para QRC
*/
typedef struct QRC_IN {
	LPSTR idQR;     //Id del QR consultado   
}vpiQrcIn_t;

/**
* Retorno para QRC
*/
typedef struct QRC_OUT {
	LPSTR respcode;           //C�digo de respuesta del host.
	LPSTR respMsg;		  //Mensaje de respuesta. 
	LPSTR authCod;     //C�digo de autorizaci�n   
	LPSTR cuponNmb;     //N�mero de cup�n
	LPSTR loteNmb;		  //N�mero de lote.
	LPSTR lastFour;	  //�ltimos 4 d�gitos de la tarjeta.
	LPSTR firstSix;	  //Primeros 6 d�gitos de la tarjeta.
	LPSTR trxDate;	  //Fecha de la transacci�n(�DD / MM / AAAA�).
	LPSTR trxHr;	  //Hora de la transacci�n(�HH:MM:SS�).
	LPSTR terminalID;	  //Terminal id.
	LPSTR medioPago;	  //Medio de Pago.
	LPSTR cardCod;	  //C�digo de Tarjeta.
	LPSTR idUnico;	  //ID Unico.
	LPSTR idBanco;	  //ID Banco.
	LPSTR emisorDscr;	  //Descripci�n de emisor.
	//ADD clarin 365
	LPSTR impTotal;	  //Importe Total
	LPSTR impCobrado;	  //Importe cobrado
	LPSTR codTarjBenef;	  //C�digo de Tarjeta Beneficio.
	LPSTR impDescuento;	  //Importe descontado
	//ADD clarin 365 FIN
}vpiQrcOut_t;

/**
* Entrada para QRT
*/
typedef struct QRT_IN {
	LPSTR ammount; //Monto
	LPSTR ticketNmb;	//N�mero de factura.
	LPSTR cantCoutas;	//Cantidad de cuotas.
	LPSTR planCod;	//C�digo de plan.
	LPSTR voidId;	//QR ID utilizado para anulaci�n
	LPSTR refundId;	//ID Para devoluciones
	LPSTR trxDate;	//Fecha de la transacci�n(�DD / MM / AAAA�)
	LPSTR imprimeTckt;	//Imprime ticket.
	LPSTR nombreComercio;	//Nombre de comercio.
	LPSTR cuitComercio;	//Cuit del comercio
	LPSTR tipoQR;	//Tipo de QR
	LPSTR merchants;	//Merchants
}vpiQrtIn_t;

/**
* Retorno para QRT
*/
typedef struct QRT_OUT {
	LPSTR respcode; //C�digo de respuesta del Terminal.
	LPSTR respMsg; //Mensaje de respuesta. 
	LPSTR idQR; //QR ID.  
	LPSTR trxDate;  //Fecha de la transacci�n(�DD / MM / AAAA�)
	LPSTR trxHr;	//Hora de la transacci�n(�HH:MM:SS�)
	LPSTR terminalId; //Terminal id	
}vpiQrtOut_t;
//ADD 1.18 Marzo 2020 FIN



/**
* Entrada para QRZ
*/
typedef struct QRZ_IN {
	LPSTR ammount; //Monto
	LPSTR cantCoutas;	//Cantidad de cuotas.
	LPSTR planCod;	//C�digo de plan.	
}vpiQrzIn_t;

typedef struct QRZ_OUT {
	LPSTR respcode;           //C�digo de respuesta del host.
	LPSTR respMsg;		  //Mensaje de respuesta. 
	LPSTR authCod;     //C�digo de autorizaci�n   
	LPSTR cuponNmb;     //N�mero de cup�n
	LPSTR loteNmb;		  //N�mero de lote.
	LPSTR lastFour;	  //�ltimos 4 d�gitos de la tarjeta.
	LPSTR firstSix;	  //Primeros 6 d�gitos de la tarjeta.
	LPSTR trxDate;	  //Fecha de la transacci�n(�DD / MM / AAAA�).
	LPSTR trxHr;	  //Hora de la transacci�n(�HH:MM:SS�).
	LPSTR terminalID;	  //Terminal id.
	LPSTR cardCod;	  //C�digo de Tarjeta.
	LPSTR impTotal;	  //Importe Total
	LPSTR impCobrado;	  //Importe cobrado	
}vpiQrzOut_t;



/**
* Entrada para FLUCAS
*/
typedef struct LUCAS_IN {
	LPSTR prodCod; //Codigo de producto
	LPSTR cardCod;	//Codigo de tarjeta
	LPSTR codComercio;	//Codigo de comercio.
	LPSTR nombreComercio;	//Nombre de comercio.
	LPSTR cuitComercio;	//Cuit del comercio
}vpiLUCASIn_t;

/**
* Retorno para LUCAS
*/
typedef struct LUCAS_OUT {
	LPSTR respcode; //C�digo de respuesta del Terminal.
	LPSTR respMsg; //Mensaje de respuesta. 
	LPSTR authCod;     //C�digo de autorizaci�n   
	LPSTR cuponNmb;     //N�mero de cup�n
	LPSTR loteNmb;		  //N�mero de lote.
	LPSTR nombreCli; //Nombre del cliente.
	LPSTR firstSix;	  //Primeros 6 d�gitos de la tarjeta.
	LPSTR lastFour;	  //�ltimos 4 d�gitos de la tarjeta.
	LPSTR trxDate;  //Fecha de la transacci�n(�DD / MM / AAAA�)
	LPSTR trxHr;	//Hora de la transacci�n(�HH:MM:SS�)
	LPSTR terminalId; //Terminal id
	LPSTR uniAcumm; //Unidades acumuladas
}vpiLUCASOut_t;

//ADD 

/**
* Entrada para FCO
*/
typedef struct FCO_IN {
	LPSTR prodCod; //Codigo de producto
	LPSTR cardCod;	//Codigo de tarjeta
	LPSTR codComercio;	//Codigo de comercio.
	LPSTR nombreComercio;	//Nombre de comercio.
	LPSTR cuitComercio;	//Cuit del comercio
}vpiFcoIn_t;

/**
* Retorno para FCO
*/
typedef struct FCO_OUT {
	LPSTR respcode; //C�digo de respuesta del Terminal.
	LPSTR respMsg; //Mensaje de respuesta. 
	LPSTR authCod;     //C�digo de autorizaci�n   
	LPSTR cuponNmb;     //N�mero de cup�n
	LPSTR loteNmb;		  //N�mero de lote.
	LPSTR nombreCli; //Nombre del cliente.
	LPSTR firstSix;	  //Primeros 6 d�gitos de la tarjeta.
	LPSTR lastFour;	  //�ltimos 4 d�gitos de la tarjeta.
	LPSTR trxDate;  //Fecha de la transacci�n(�DD / MM / AAAA�)
	LPSTR trxHr;	//Hora de la transacci�n(�HH:MM:SS�)
	LPSTR terminalId; //Terminal id
	LPSTR uniAcumm; //Unidades acumuladas
}vpiFcoOut_t;
/**
* Entrada para FRE
*/
typedef struct FRE_IN {
	LPSTR prodCod; //Codigo de producto
	LPSTR uniRed; //Unidades a redimir
	LPSTR cardCod;	//Codigo de tarjeta
	LPSTR codComercio;	//Codigo de comercio.
	LPSTR nombreComercio;	//Nombre de comercio.
	LPSTR cuitComercio;	//Cuit del comercio
}vpiFreIn_t;

/**
* Retorno para FRE
*/
typedef struct FRE_OUT {
	LPSTR respcode; //C�digo de respuesta del Terminal.
	LPSTR respMsg; //Mensaje de respuesta. 
	LPSTR authCod;     //C�digo de autorizaci�n   
	LPSTR cuponNmb;     //N�mero de cup�n
	LPSTR loteNmb;		  //N�mero de lote.
	LPSTR nombreCli; //Nombre del cliente.
	LPSTR firstSix;	  //Primeros 6 d�gitos de la tarjeta.
	LPSTR lastFour;	  //�ltimos 4 d�gitos de la tarjeta.
	LPSTR trxDate;  //Fecha de la transacci�n(�DD / MM / AAAA�)
	LPSTR trxHr;	//Hora de la transacci�n(�HH:MM:SS�)
	LPSTR terminalId; //Terminal id
	LPSTR saldoUni; //Saldo de unidades
}vpiFreOut_t;

/**
* Entrada para FCA
*/
typedef struct FCA_IN {
	LPSTR prodCod; //Codigo de producto 20
	LPSTR uniRed; //Unidades a redimir 
	LPSTR cardCod;	//Codigo de tarjeta
	LPSTR codComercio;	//Codigo de comercio.
	LPSTR nombreComercio;	//Nombre de comercio.
	LPSTR cuitComercio;	//Cuit del comercio
}vpiFcaIn_t;

/**
* Retorno para FCA
*/
typedef struct FCA_OUT {
	LPSTR respcode; //C�digo de respuesta del Terminal.
	LPSTR respMsg; //Mensaje de respuesta. 
	LPSTR authCod;     //C�digo de autorizaci�n   
	LPSTR cuponNmb;     //N�mero de cup�n
	LPSTR loteNmb;		  //N�mero de lote.
	LPSTR nombreCli; //Nombre del cliente.
	LPSTR firstSix;	  //Primeros 6 d�gitos de la tarjeta.
	LPSTR lastFour;	  //�ltimos 4 d�gitos de la tarjeta.
	LPSTR trxDate;  //Fecha de la transacci�n(�DD / MM / AAAA�)
	LPSTR trxHr;	//Hora de la transacci�n(�HH:MM:SS�)
	LPSTR terminalId; //Terminal id
	LPSTR saldoUni; //Saldo de unidades
	LPSTR operationCode; // Codigo de operacion
}vpiFcaOut_t;
/**
* Entrada para FAC
*/
typedef struct FAC_IN {
	LPSTR prodCod; //Codigo de producto 20
	LPSTR uniAcum; //Unidades a acumular 
}vpiFacIn_t;

/**
* Retorno para FAC
*/
typedef struct FAC_OUT {
	LPSTR respcode; //C�digo de  respuesta del Terminal.
	LPSTR respMsg; //Mensaje de respuesta. 
	LPSTR authCod;     //C�digo de autorizaci�n   
	LPSTR cuponNmb;     //N�mero de cup�n
	LPSTR loteNmb;		  //N�mero de lote.
	LPSTR nombreCli; //Nombre del cliente.
	LPSTR firstSix;	  //Primeros 6 d�gitos de la tarjeta.
	LPSTR lastFour;	  //�ltimos 4 d�gitos de la tarjeta.
	LPSTR trxDate;  //Fecha de la transacci�n(�DD / MM / AAAA�)
	LPSTR trxHr;	//Hora de la transacci�n(�HH:MM:SS�)
	LPSTR terminalId; //Terminal id
	LPSTR saldoUni; //Saldo de unidades
	LPSTR operationCode; // Codigo de operacion
}vpiFacOut_t;

/**
* Entrada para FAN
*/
typedef struct FAN_IN {
	LPSTR cuponNmb;     //N�mero de cup�n	
}vpiFanIn_t;

/**
* Retorno para FAN
*/
typedef struct FAN_OUT {
	LPSTR respcode; //C�digo de respuesta del Terminal.
	LPSTR respMsg; //Mensaje de respuesta. 
	LPSTR authCod;     //C�digo de autorizaci�n   
	LPSTR cuponNmb;     //N�mero de cup�n
	LPSTR loteNmb;		  //N�mero de lote.
	LPSTR nombreCli; //Nombre del cliente.
	LPSTR firstSix;	  //Primeros 6 d�gitos de la tarjeta.
	LPSTR lastFour;	  //�ltimos 4 d�gitos de la tarjeta.
	LPSTR trxDate;  //Fecha de la transacci�n(�DD / MM / AAAA�)
	LPSTR trxHr;	//Hora de la transacci�n(�HH:MM:SS�)
	LPSTR terminalId; //Terminal id
	LPSTR saldoUni; //Saldo de unidades
	LPSTR operationCode; // Codigo de operacion
}vpiFanOut_t;
/**
* Entrada para FAR
*/
typedef struct FAR_IN {
	LPSTR prodCod; //Codigo de producto
	LPSTR cardCod;	//Codigo de tarjeta
	LPSTR cuponNum;	//Numero de cupon
}vpiFarIn_t;

/**
* Retorno para FAR
*/
typedef struct FAR_OUT {
	LPSTR respcode; //C�digo de respuesta del Terminal.
	LPSTR respMsg; //Mensaje de respuesta. 
	LPSTR authCod;     //C�digo de autorizaci�n   
	LPSTR cuponNmb;     //N�mero de cup�n
	LPSTR loteNmb;		  //N�mero de lote.
	LPSTR nombreCli; //Nombre del cliente.
	LPSTR firstSix;	  //Primeros 6 d�gitos de la tarjeta.
	LPSTR lastFour;	  //�ltimos 4 d�gitos de la tarjeta.
	LPSTR trxDate;  //Fecha de la transacci�n(�DD / MM / AAAA�)
	LPSTR trxHr;	//Hora de la transacci�n(�HH:MM:SS�)
	LPSTR terminalId; //Terminal id
	LPSTR saldoUni; //Saldo de unidades
}vpiFarOut_t;

//ADD compativilidad VPI viejo
/*
	Entrada para FCO compatible con VPI viejo
*/
typedef struct LOYALTY_BALANCE_IN {

	LPSTR productCode;
	//LPSTR amount;
	LPSTR issuerCode;		// C�digo de tarjeta 
	LPSTR merchantCode;		// C�digo de comercio a utilizar
	LPSTR merchantName;		// Razon social del comercio
	LPSTR cuit;				// CUIT del comercio

} vpiLoyaltyBalanceIn_t;

/*
	Entrada para FRE compatible con VPI viejo
*/
typedef struct LOYALTY_REDEEM_IN {

	LPSTR productCode;
	LPSTR amount;
	LPSTR issuerCode;		// C�digo de tarjeta 
	LPSTR merchantCode;		// C�digo de comercio a utilizar
	LPSTR merchantName;		// Razon social del comercio
	LPSTR cuit;				// CUIT del comercio


} vpiLoyaltyRedeemIn_t;


/*
	Entrada para FAR compatible con VPI viejo
*/
typedef struct LOYALTY_VOID_IN {

	LPSTR amount;			// Monto *100  

} vpiLoyaltyVoidIn_t;



typedef struct GETVERSION_OUT {

	LPSTR versionMessage;  // Mensaje de respuesta de version 

} vpiGetVersion_t;
/*
	Salida para FAR, FCO y FRE compatible con VPI viejo
*/
typedef struct LOYALTY_OUT {
	LPSTR hostRespCode;	// C�digo de respuesta del host   
	LPSTR hostMessage;  // Mensaje de respuesta del host   
	LPSTR authCode;     // N�mero de autorizaci�n   
	LPSTR ticketNumber; // N�mero de cup�n   
	LPSTR batchNumber;  // N�mero de lote   
	LPSTR customerName; // Nombre del tarjeta-habiente   
	/* Eldar MOD ---> */

	//------------ 2091202 fix ?
	LPSTR panLast4;     // Ultimo 4 digitos de la tarjeta   
	LPSTR panFirst6;      	// Primeros 6 digitos de la tarjeta
	//--------------

	/* <--- Eldar MOD */

	LPSTR date;         // Fecha de la transacci�n   
	LPSTR time;         // Hora de la transaccion
	LPSTR terminalID;
	LPSTR amount;			// Monto de unidades
} vpiLoyaltyOut_t;
//ADD compativilidad VPI viejo FIN
//ADD Fidelidad FIN

/**
* Retorno de OTE
*/
typedef struct OTE_OUT {

	WORD index;        //�ndice del registro.
	LPSTR codProc;	   //Codigo de procesador.
	LPSTR issuerCode;  //C�digo de tarjeta   
	LPSTR cardName;	   //Nombre de la tarjeta.
	LPSTR merchant;    //Numero de establecimiento
	LPSTR groupName;   //Nombre del Grupo
	LPSTR terminalID;  //Terminal ID

}vpiOteOut_t;

/**
* Retorno de REV
*/
typedef struct REV_OUT {

	LPSTR respCode;	   //Codigo de respuesta.
	LPSTR respMsg;     //Mensaje de respuesta.   
	LPSTR date;		   // Fecha ("DD/MM/AAAA")  
	LPSTR time;		   // Hora ("HH:MM:SS")
	LPSTR terminalID;  //Terminal ID

}vpiRevOut_t;

/**
*/
typedef struct ISSUER_OUT{   

	WORD index;           //�ndice del registro.		//LFT 
	LPSTR acquirerCode;   //C�digo de procesador.   
	LPSTR issuerCode;     //C�digo de tarjeta   
	LPSTR issuerName;     //Nombre de la tarjeta   
	LPSTR maxInstCount;   //Maxima cantidad de cuotas
	LPSTR terminalID;

}vpiIssuerOut_t;

/**
*/
typedef struct PLAN_OUT{   
	
	WORD index;        //�ndice del registro.   		//LFT  
	LPSTR issuerCode;  //C�digo de tarjeta   
	LPSTR planCode;    //C�digo de plan   
	LPSTR planLabel;   //Nombre del plan
	LPSTR terminalID;

}vpiPlanOut_t;

/**
*/
typedef struct VERSION_OUT{   
	
	WORD version;            //Version del VPI.   		//LFT  

}vpiVersionOut_t;

/**
*/
typedef struct CLASSIC_MESSAGE_ARRAY {

	BYTE* msg;
	int msgLen;

}vpiClsMessageArray_t;

/**
*/
typedef struct CLASSIC_MESSAGE {

	BYTE header[2]; //CLA_INS
	BYTE modoIntegracion;
	BYTE versionMensaje;
	BYTE p2;
	BYTE LC[2];
	BYTE* data;
	BYTE TOU[2];

}vpiClsMessage_t;

/**
*/
typedef struct PRI_OUT {

//	WORD index;           //�ndice del registro.
	LPSTR issuerCode;	  //C�digo de tarjeta   
	LPSTR panFirst6;	  //BIN de la tarjeta.   
	LPSTR panLast4;    //Ultimos cuatro digitos de la tarjeta   
	LPSTR terminalID;	  //Numero de la terminal

}vpiPriOut;

/*--------------------------METODOS LEGACY --------------------------*/

/**
* Abre el puerto serial de comunicaciones para poder enviar y recibir
* los comandos.El puerto debe estar cerrado para que la ejecuci�n sea 
* exitosa.Es necesario para ejecutar el resto de los comandos.
* @param params Par�metros de configuracion del puerto serial.
*
* @return VPI_OK Puerto abierto exitosamente	
* @return VPI_FAIL El puerto se encontraba abierto o no se pudo abrir.
*/
WORD __stdcall vpiOpenPort (comParams_t* params);

/**
* Cierra el puerto serial de comunicaciones y lo deja libre para otras
* aplicaciones. El puerto debe estar abierto para que la ejecuci�n sea 
* exitosa.Luego de ejecutar este comando, no se puede ejecutar ningun 
* otro comando.
* @return VPI_OK Puerto cerrado exitosamente
* @return VPI_FAIL El puerto no se encontraba abierto o no se pudo cerrar.
*/
WORD __stdcall vpiClosePort(void);

/**
* Env�a un mensaje por el puerto y espera la respuesta al mismo en forma 
* sincr�nica, para verificar que la conexi�n con el POS est� OK.La 
* aplicaci�n queda esperando hasta tenga la respuesta o bien expire el
* timeout default.El puerto debe estar abierto para que la ejecuci�n sea exitosa.
* @return VPI_OK Conexi�n exitosa.
* @return VPI_FAIL No se pudo enviar el comando posiblemente el puerto est� cerrado.
* @return VPI_TIMEOUT_EXP Timeout de respuesta expirado sin respuesta.
*/
WORD __stdcall vpiTestConnection(void);

/**
* Env�a la orden de realizar una venta y espera la respuesta de la misma en forma
* sincr�nica.La aplicaci�n queda esperando hasta tenga la respuesta o bien expire
* el timeout especificado.El puerto debe estar abierto para que la ejecuci�n sea 
* exitosa.
* @param input Estructura con los datos de entrada de la venta.
* @param output Estructura con los datos de respuesta de la venta. 
*               Se completa dentro de la funci�n
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK
* @return VPI_FAIL
* @return VPI_TIMEOUT_EXP
* @return VPI_INVALID_ISSUER
* @return VPI_INVALID_PLAN
* @return VPI_TRX_CANCELED
* @return VPI_DIF_CARD
* @return VPI_INVALID_CARD
* @return VPI_EXPIRED_CARD
* @return VPI_ERR_COM
* @return VPI_ERR_PRINT
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall vpiPurchase(vpiPurchaseIn_t* intput, vpiTrxOut_t* output, LONG timeout);

/**
* Env�a la orden de realizar una venta con credito directo 
* y espera la respuesta de la misma en forma sincr�nica.
* La aplicaci�n queda esperando hasta tenga la respuesta o bien expire
* el timeout especificado.El puerto debe estar abierto para que la ejecuci�n sea
* exitosa.
* @param input Estructura con los datos de entrada de la venta.
* @param output Estructura con los datos de respuesta de la venta.
*               Se completa dentro de la funci�n
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK
* @return VPI_FAIL
* @return VPI_TIMEOUT_EXP
* @return VPI_INVALID_ISSUER
* @return VPI_INVALID_PLAN
* @return VPI_TRX_CANCELED
* @return VPI_DIF_CARD
* @return VPI_INVALID_CARD
* @return VPI_EXPIRED_CARD
* @return VPI_ERR_COM
* @return VPI_ERR_PRINT
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall vpiPurchaseCreditoDirecto(vpiPurchaseIn_t* input, vpiTrxMarkOut1_t* output, LONG timeout);

/**
* Env�a la orden de realizar una consulta de credito directo
* y espera la respuesta de la misma en forma sincr�nica.
* La aplicaci�n queda esperando hasta tenga la respuesta o bien expire
* el timeout especificado.El puerto debe estar abierto para que la ejecuci�n sea
* exitosa.
* @param input Estructura con los datos de entrada de la venta.
* @param output Estructura con los datos de respuesta de la venta.
*               Se completa dentro de la funci�n
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK
* @return VPI_FAIL
* @return VPI_TIMEOUT_EXP
* @return VPI_INVALID_ISSUER
* @return VPI_INVALID_PLAN
* @return VPI_TRX_CANCELED
* @return VPI_DIF_CARD
* @return VPI_INVALID_CARD
* @return VPI_EXPIRED_CARD
* @return VPI_ERR_COM
* @return VPI_ERR_PRINT
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall vpiConsultaCreditoDirecto(vpiPurchaseIn_t* input, vpiCcdMarkOut_t* output, LONG timeout);

/**
* Env�a la orden de realizar una venta con extra cash 
* y espera la respuesta de la misma en forma sincr�nica.
* La aplicaci�n queda esperando hasta tenga la respuesta o bien expire
* el timeout especificado.El puerto debe estar abierto para que la ejecuci�n sea
* exitosa.
* @param input Estructura con los datos de entrada de la venta.
* @param output Estructura con los datos de respuesta de la venta.
*               Se completa dentro de la funci�n
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK
* @return VPI_FAIL
* @return VPI_TIMEOUT_EXP
* @return VPI_INVALID_ISSUER
* @return VPI_INVALID_PLAN
* @return VPI_TRX_CANCELED
* @return VPI_DIF_CARD
* @return VPI_INVALID_CARD
* @return VPI_EXPIRED_CARD
* @return VPI_ERR_COM
* @return VPI_ERR_PRINT
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall vpiPurchaseExtraCash(vpiPurchaseIn_t* intput, vpiTrxOut_t* output, LONG timeout);

/**
* Env�a la orden de realizar una venta con retorno de marca
* y espera la respuesta de la misma en forma sincr�nica.
* La aplicaci�n queda esperando hasta tenga la respuesta o bien expire
* el timeout especificado.El puerto debe estar abierto para que la ejecuci�n sea
* exitosa.
* @param input Estructura con los datos de entrada de la venta.
* @param output Estructura con los datos de respuesta de la venta.
*               Se completa dentro de la funci�n
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK
* @return VPI_FAIL
* @return VPI_TIMEOUT_EXP
* @return VPI_INVALID_ISSUER
* @return VPI_INVALID_PLAN
* @return VPI_TRX_CANCELED
* @return VPI_DIF_CARD
* @return VPI_INVALID_CARD
* @return VPI_EXPIRED_CARD
* @return VPI_ERR_COM
* @return VPI_ERR_PRINT
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall vpiPurchaseMark(vpiPurchaseIn_t* intput, vpiTrxMarkOut1_t* output, LONG timeout);

/**
* Env�a la orden de realizar una venta extra cash con retorno de marca
* y espera la respuesta de la misma en forma sincr�nica.
* La aplicaci�n queda esperando hasta tenga la respuesta o bien expire
* el timeout especificado.El puerto debe estar abierto para que la ejecuci�n sea
* exitosa.
* @param input Estructura con los datos de entrada de la venta.
* @param output Estructura con los datos de respuesta de la venta.
*               Se completa dentro de la funci�n
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK
* @return VPI_FAIL
* @return VPI_TIMEOUT_EXP
* @return VPI_INVALID_ISSUER
* @return VPI_INVALID_PLAN
* @return VPI_TRX_CANCELED
* @return VPI_DIF_CARD
* @return VPI_INVALID_CARD
* @return VPI_EXPIRED_CARD
* @return VPI_ERR_COM
* @return VPI_ERR_PRINT
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall vpiPurchaseExtraCashMark(vpiPurchaseIn_t* intput, vpiTrxMarkOut1_t* output, LONG timeout);

/**
* Env�a la orden de realizar una venta que no elimina el reverso
* y espera la respuesta de la misma en forma sincr�nica.
* La aplicaci�n queda esperando hasta tenga la respuesta o bien expire
* el timeout especificado.El puerto debe estar abierto para que la ejecuci�n sea
* exitosa. No borra reverso
* @param input Estructura con los datos de entrada de la venta.
* @param output Estructura con los datos de respuesta de la venta.
*               Se completa dentro de la funci�n
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK
* @return VPI_FAIL
* @return VPI_TIMEOUT_EXP
* @return VPI_INVALID_ISSUER
* @return VPI_INVALID_PLAN
* @return VPI_TRX_CANCELED
* @return VPI_DIF_CARD
* @return VPI_INVALID_CARD
* @return VPI_EXPIRED_CARD
* @return VPI_ERR_COM
* @return VPI_ERR_PRINT
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall vpiPurchaseRev(vpiPurchaseIn_t* intput, vpiTrxMarkOut_t* output, LONG timeout);

/**
* Env�a la orden de eliminar reverso si existe
* @param input Estructura con los datos de entrada de la venta.
* @param output Estructura con los datos de respuesta de la venta.
*               Se completa dentro de la funci�n
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK
* @return VPI_FAIL
* @return VPI_TIMEOUT_EXP
* @return VPI_INVALID_ISSUER
* @return VPI_INVALID_PLAN
* @return VPI_TRX_CANCELED
* @return VPI_DIF_CARD
* @return VPI_INVALID_CARD
* @return VPI_EXPIRED_CARD
* @return VPI_ERR_COM
* @return VPI_ERR_PRINT
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall vpiDeleteRev(vpiRevDeleteIn_t* intput, vpiRevOut_t* output, LONG timeout);

/**
* Env�a la orden de realizar una venta con multiples establecimientos
* y espera la respuesta de la misma en forma sincr�nica.
* La aplicaci�n queda esperando hasta tenga la respuesta o bien expire
* el timeout especificado.El puerto debe estar abierto para que la ejecuci�n sea
* exitosa.
* @param input Estructura con los datos de entrada de la venta.
* @param output Estructura con los datos de respuesta de la venta.
*               Se completa dentro de la funci�n
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK
* @return VPI_FAIL
* @return VPI_TIMEOUT_EXP
* @return VPI_INVALID_ISSUER
* @return VPI_INVALID_PLAN
* @return VPI_TRX_CANCELED
* @return VPI_DIF_CARD
* @return VPI_INVALID_CARD
* @return VPI_EXPIRED_CARD
* @return VPI_ERR_COM
* @return VPI_ERR_PRINT
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall vpiPurchaseGroup(vpiPurchaseGroupIn_t* intput, vpiTrxGroupOut_t* output, LONG timeout);

/**
* Env�a la orden de realizar una venta extra cash con multiples establecimientos
* y espera la respuesta de la misma en forma sincr�nica.
* La aplicaci�n queda esperando hasta tenga la respuesta o bien expire
* el timeout especificado.El puerto debe estar abierto para que la ejecuci�n sea
* exitosa.
* @param input Estructura con los datos de entrada de la venta.
* @param output Estructura con los datos de respuesta de la venta.
*               Se completa dentro de la funci�n
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK
* @return VPI_FAIL
* @return VPI_TIMEOUT_EXP
* @return VPI_INVALID_ISSUER
* @return VPI_INVALID_PLAN
* @return VPI_TRX_CANCELED
* @return VPI_DIF_CARD
* @return VPI_INVALID_CARD
* @return VPI_EXPIRED_CARD
* @return VPI_ERR_COM
* @return VPI_ERR_PRINT
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall vpiPurchaseGroupExtraCash(vpiPurchaseGroupIn_t* intput, vpiTrxGroupOut_t* output, LONG timeout);

/**
* Env�a la orden de realizar una anulaci�n de venta y espera la respuesta de la misma
* en forma sincr�nica.La aplicaci�n queda esperando hasta tenga la respuesta o bien 
* expire el timeout especificado.El puerto debe estar abierto para que la ejecuci�n 
* sea exitosa.
* @param input Estructura con los datos de entrada de la anulaci�n.
* @param output Estructura con los datos de respuesta de la anulaci�n. 
*               Se completa dentro de la funci�n.
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return 	VPI_OK
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_ISSUER
* @return 	VPI_INVALID_TICKET
* @return 	VPI_EMPTY_BATCH
* @return 	VPI_TRX_CANCELED
* @return 	VPI_DIF_CARD
* @return 	VPI_INVALID_CARD
* @return 	VPI_EXPIRED_CARD
* @return 	VPI_INVALID_TRX 
* @return 	VPI_ERR_COM
* @return 	VPI_ERR_PRINT

*/
WORD __stdcall vpiVoid(vpiVoidIn_t* intput, vpiTrxOut_t* output, LONG timeout);

/**
* Env�a la orden de realizar una devoluci�n y espera la respuesta de la misma en 
* forma sincr�nica.La aplicaci�n queda esperando hasta tenga la respuesta o bien
* expire el timeout especificado.El puerto debe estar abierto para que la ejecuci�n
* sea exitosa.
* @param input Estructura con los datos de entrada de la devoluci�n.
* @param output Estructura con los datos de respuesta de la devoluci�n. 
*               Se completa dentro de la funci�n.
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK Conexi�n exitosa.
* @return VPI_FAIL No se pudo enviar el comando.
* @return VPI_TIMEOUT_EXP Timeout de respuesta expirado sin respuesta.
* @return VPI_INVALID_ISSUER El c�digo de tarjeta no existe.
* @return VPI_INVALID_PLAN El c�digo de plan no existe.
* @return VPI_TRX_CANCELED Transacci�n cancelada por el usuario.
* @return VPI_DIF_CARD La tarjeta deslizada por el usuario no coincide con la pedida.
* @return VPI_INVALID_CARD La tarjeta deslizada no es v�lida.
* @return VPI_EXPIRED_CARD La tarjeta deslizada est� vencida.
* @return VPI_ERR_COM El POS no pudo comunicarse con el host.
* @return VPI_ERR_PRINT El POS no pudo imprimir el ticket.
* @return VPI_INVALID_IN_CMD Nombre del comando inexistente.
* @return VPI_INVALID_IN_LEN Largo de los par�metros inv�lido para este comando.
* @return VPI_INVALID_IN_PARAM Formato de alg�n par�metro no es correcto.
* @return VPI_INVALID_OUT_CMD Nombre del comando devuelto no coincide con el enviado.
* @return VPI_INVALID_OUT_LEN Largo de los par�metros devueltos inv�lido para este comando.
* @return VPI_INVALID_OUT_PARAM Formato de alg�n par�metro devuelto no es correcto.
* @return VPI_GENERAL_FAIL Error general en la operaci�n.
*/
WORD __stdcall vpiRefund (vpiRefundIn_t* input, vpiTrxOut_t* output, LONG timeout);

/**
* Env�a la orden de realizar una anulaci�n de devoluci�n y espera la respuesta
* de la misma en forma sincr�nica.La aplicaci�n queda esperando hasta tenga la 
* respuesta o bien expire el timeout especificado.El puerto debe estar abierto 
* para que la ejecuci�n sea exitosa.
* @param input Estructura con los datos de entrada de la anulaci�n.
* @param output Estructura con los datos de respuesta de la anulaci�n. 
*               Se completa dentro de la funci�n.
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return 	VPI_OK
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_ISSUER
* @return 	VPI_INVALID_TICKET
* @return 	VPI_EMPTY_BATCH
* @return 	VPI_TRX_CANCELED
* @return 	VPI_DIF_CARD
* @return 	VPI_INVALID_CARD
* @return 	VPI_EXPIRED_CARD
* @return 	VPI_INVALID_TRX 
* @return 	VPI_ERR_COM
* @return 	VPI_ERR_PRINT
*/
WORD __stdcall vpiRefundVoid(vpiVoidIn_t* intput, vpiTrxOut_t* output, LONG timeout); 

/**
* Env�a la orden de realizar un cierre de lote. La aplicaci�n queda esperando hasta
* tenga la respuesta o bien expire el timeout especificado. El puerto debe estar 
* abierto para que la ejecuci�n sea exitosa.
* @param output Estructura con el resultado de la operaci�n contra el host. 
*               Se completa dentro de la funci�n.
* @param timeout Tiempo de espera de respuesta en segundos.
* 
* @return 	VPI_OK
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_TRX_CANCELED
* @return 	VPI_ERR_COM
* @return 	VPI_ERR_PRINT
*/
WORD __stdcall vpiBatchClose(vpiBatchCloseOut_t* output, LONG timeout);

/**
* Env�a la orden de obtener la informaci�n de la �ltima transacci�n realizada 
* y espera la respuesta de la misma en forma sincr�nica.La aplicaci�n queda 
* esperando hasta tenga la respuesta o bien expire el timeout especificado.
* El puerto debe estar abierto para que la ejecuci�n sea exitosa.
* @param trxCode C�digo del tipo de transacci�n: VPI_PURCHASE, VPI_VOID, 
                                                 VPI_REFUND, VPI_REFUND_VOID
*
* @param output Estructura con los datos de respuesta de la �ltima transacci�n realizada. 
*               Se completa dentro de la funci�n.
*
* @return 	VPI_OK
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_PARAM
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_ISSUER
* @return 	VPI_INVALID_TICKET
* @return 	VPI_INVALID_PLAN
* @return 	VPI_EMPTY_BATCH
* @return 	VPI_TRX_CANCELED
* @return 	VPI_DIF_CARD
* @return 	VPI_INVALID_CARD
* @return 	VPI_EXPIRED_CARD
* @return 	VPI_ERR_COM
* @return 	VPI_ERR_PRINT
*/
WORD __stdcall vpiGetLastTrxData(WORD* trxCode, vpiTrxOut_t* output);


/**
* Env�a la orden de obtener un determinado registro, con los totales por tarjeta 
* del �ltimo cierre realizado y espera la respuesta de la misma en forma 
* sincr�nica.Para obtener todos los registros se debe hacer un ciclo desde 0  
* hasta que el c�digo de respuesta sea distinto de VPI_MORE_REC. La aplicaci�n queda esperando 
* hasta tenga la respuesta o bien expire el timeout especificado. El puerto debe 
* estar abierto para que la ejecuci�n sea exitosa.
*
* @param index Indice del registro que deseo recuperar
* @param output Estructura con la informaci�n del registro que quiero.
*
* @return VPI_OK Fin de registros.
* @return VPI_MORE_REC Quedan registros.
* @return VPI_FAIL No se pudo enviar el comando
* @return VPI_TIMEOUT_EXP Timeout de respuesta expirado sin respuesta.
* @return VPI_INVALID_INDEX El indice del registro no existe. 
* @return VPI_TRX_CANCELED Transacci�n cancelada por el usuario.
* @return VPI_INVALID_TRX No se realizo el cierre.
* @return VPI_INVALID_IN_CMD 
* @return VPI_INVALID_IN_LEN
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_INVALID_OUT_LEN
* @return VPI_INVALID_OUT_PARAM
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall vpiGetBatchCloseData(WORD index, vpiBatchCloseDataOut_t* output);

/**
* Env�a la orden de re-imprimir el ticket de la �ltima transacci�n.La aplicaci�n queda 
* esperando hasta tenga la respuesta o bien expire el timeout default.El puerto debe 
* estar abierto para que la ejecuci�n sea exitosa.
*
* @param Ninguno
*
* @return 	VPI_OK
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD 
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_PARAM
* @return 	VPI_GENERAL_FAIL
*/
WORD __stdcall vpiPrintTicket(void);

/**
* Env�a la orden de re-imprimir el ticket del �ltimo cierre de lote. La aplicaci�n queda
* esperando hasta tenga la respuesta o bien expire el timeout default.El puerto debe estar
* abierto para que la ejecuci�n sea exitosa.
* 
* @param Ninguno
* 
* @return 	VPI_OK
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD 
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_PARAM
* @return 	VPI_GENERAL_FAIL
*/
WORD __stdcall vpiPrintBatchClose(void);

/**
* Env�a el comando para obtener un registro de la tabla de tarjetas del POS y espera 
* la respuesta de la misma en forma sincr�nica. Para obtener todos los registros se 
* debe hacer un ciclo desde 0 hasta que el c�digo de respuesta sea distinto de VPI_MORE_REC.
* La aplicaci�n queda  esperando hasta tenga la respuesta o bien expire el timeout especificado. 
* El puerto debe estar abierto para que la ejecuci�n sea exitosa.
*
* @param index Indice del registro a obtener.
* @param output Estructura con los datos de la tarjeta. Se completa dentro de la funci�n.
*
* @return 	VPI_OK
* @return 	VPI_MORE_REC
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD 
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_INDEX
*/
WORD __stdcall vpiGetIssuer(WORD index, vpiIssuerOut_t* output);

/**
* Env�a el comando para obtener un registro de la tabla de planes del POS y espera la 
* respuesta de la misma en forma sincr�nica. Para obtener todos los registros se debe
* hacer un ciclo desde 0 hasta que el c�digo de respuesta sea distinto de VPI_MORE_REC.
* La aplicaci�n queda esperando hasta tenga la respuesta o bien expire el timeout 
* especificado. El puerto debe estar abierto para que la ejecuci�n sea exitosa.
*
* @param index Indice del registro a obtener.
* @param output Estructura con los datos del plan. Se completa dentro de la funci�n.
*
* @return 	VPI_OK
* @return 	VPI_MORE_REC
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD 
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_INDEX
*/
WORD __stdcall vpiGetPlan(WORD index, vpiPlanOut_t* output);

/**
* Env�a el comando para obtener un registro de la tabla de grupos del POS y espera la
* respuesta de la misma en forma sincr�nica. Para obtener todos los registros se debe
* hacer un ciclo desde 0 hasta que el c�digo de respuesta sea distinto de VPI_MORE_REC.
* La aplicaci�n queda esperando hasta tenga la respuesta o bien expire el timeout
* especificado. El puerto debe estar abierto para que la ejecuci�n sea exitosa.
*
* @param index Indice del registro a obtener.
* @param output Estructura con los datos del plan. Se completa dentro de la funci�n.
*
* @return 	VPI_OK
* @return 	VPI_MORE_REC
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_INDEX
*/
WORD __stdcall vpiGetOTE(WORD index, vpiOteOut_t* output);

/**
* Env�a el comando para registrar un nuevo grupo y espera la
* respuesta de la misma en forma sincr�nica. Para obtener todos los registros se debe
* hacer un ciclo desde 0 hasta que el c�digo de respuesta sea distinto de VPI_MORE_REC.
* La aplicaci�n queda esperando hasta tenga la respuesta o bien expire el timeout
* especificado. El puerto debe estar abierto para que la ejecuci�n sea exitosa.
*
* @param index Indice del registro a obtener.
* @param output Estructura con los datos del plan. Se completa dentro de la funci�n.
*
* @return 	VPI_OK
* @return 	VPI_MORE_REC
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_INDEX
*/
WORD __stdcall vpiGetIES(vpiIesIn_t* input, vpiIesOut_t* output, LONG timeout);

//ADD 1.18 Marzo 2020
/**
* Env�a el comando para consultar el estado de un QR y espera la
* respuesta de la misma en forma sincr�nica. Para obtener todos los registros se debe
* hacer un ciclo desde 0 hasta que el c�digo de respuesta sea distinto de VPI_MORE_REC.
* La aplicaci�n queda esperando hasta tenga la respuesta o bien expire el timeout
* especificado. El puerto debe estar abierto para que la ejecuci�n sea exitosa.
*
* @param input Estructura con los datos de entrada para el POS.
* @param output Estructura con los datos del plan. Se completa dentro de la funci�n.
*
* @return 	VPI_OK
* @return 	VPI_MORE_REC
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_INDEX
*/
WORD __stdcall vpiGetQRC(vpiQrcIn_t* input, vpiQrcOut_t* output, LONG timeout);

/**
* Env�a el comando para la generaci�n de un QR y espera la
* respuesta de la misma en forma sincr�nica. Para obtener todos los registros se debe
* hacer un ciclo desde 0 hasta que el c�digo de respuesta sea distinto de VPI_MORE_REC.
* La aplicaci�n queda esperando hasta tenga la respuesta o bien expire el timeout
* especificado. El puerto debe estar abierto para que la ejecuci�n sea exitosa.
*
* @param input Estructura con los datos de entrada para el POS.
* @param output Estructura con los datos del plan. Se completa dentro de la funci�n.
*
* @return 	VPI_OK
* @return 	VPI_MORE_REC
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_INDEX
*/
WORD __stdcall vpiGetQRT(vpiQrtIn_t* input, vpiQrtOut_t* output, LONG timeout);
//ADD 1.18 Marzo 2020 FIN
//ADD Fidelidad
/**
* Env�a el comando para consultar el estado de un QR y espera la
* respuesta de la misma en forma sincr�nica. Para obtener todos los registros se debe
* hacer un ciclo desde 0 hasta que el c�digo de respuesta sea distinto de VPI_MORE_REC.
* La aplicaci�n queda esperando hasta tenga la respuesta o bien expire el timeout
* especificado. El puerto debe estar abierto para que la ejecuci�n sea exitosa.
*
* @param input Estructura con los datos de entrada para el POS.
* @param output Estructura con los datos del plan. Se completa dentro de la funci�n.
*
* @return 	VPI_OK
* @return 	VPI_MORE_REC
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_INDEX
*/
WORD __stdcall vpiGetFCO(vpiFcoIn_t* input, vpiFcoOut_t* output, LONG timeout);

/**
* Env�a el comando para la generaci�n de un QR y espera la
* respuesta de la misma en forma sincr�nica. Para obtener todos los registros se debe
* hacer un ciclo desde 0 hasta que el c�digo de respuesta sea distinto de VPI_MORE_REC.
* La aplicaci�n queda esperando hasta tenga la respuesta o bien expire el timeout
* especificado. El puerto debe estar abierto para que la ejecuci�n sea exitosa.
*
* @param input Estructura con los datos de entrada para el POS.
* @param output Estructura con los datos del plan. Se completa dentro de la funci�n.
*
* @return 	VPI_OK
* @return 	VPI_MORE_REC
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_INDEX
*/
WORD __stdcall vpiGetFRE(vpiFreIn_t* input, vpiFreOut_t* output, LONG timeout);

/**
* Env�a el comando para la generaci�n de un QR y espera la
* respuesta de la misma en forma sincr�nica. Para obtener todos los registros se debe
* hacer un ciclo desde 0 hasta que el c�digo de respuesta sea distinto de VPI_MORE_REC.
* La aplicaci�n queda esperando hasta tenga la respuesta o bien expire el timeout
* especificado. El puerto debe estar abierto para que la ejecuci�n sea exitosa.
*
* @param input Estructura con los datos de entrada para el POS.
* @param output Estructura con los datos del plan. Se completa dentro de la funci�n.
*
* @return 	VPI_OK
* @return 	VPI_MORE_REC
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_INDEX
*/
WORD __stdcall vpiGetFAR(vpiFarIn_t* input, vpiFarOut_t* output, LONG timeout);

//ADD compativilidad VPI viejo
/*
	Procesamiento FCO vpi viejo
*/
WORD __stdcall vpiLoyaltyBalance(vpiLoyaltyBalanceIn_t* input, vpiLoyaltyOut_t* output, LONG timeout);
WORD UnMountLoyaltyResp(vpiLoyaltyOut_t* data, char* buffer);
WORD MountLoyaltyBalance(char* buffer, vpiLoyaltyBalanceIn_t* data);

/*
	Procesamiento FRE vpi viejo
*/
WORD __stdcall vpiLoyaltyRedeem(vpiLoyaltyRedeemIn_t* input, vpiLoyaltyOut_t* output, LONG timeout);
WORD MountLoyaltyRedeem(char* buffer, vpiLoyaltyRedeemIn_t* data);

/*
	Procesamiento FAR vpi viejo
*/
WORD __stdcall vpiLoyaltyVoid(vpiLoyaltyVoidIn_t* input, vpiLoyaltyOut_t* output, LONG timeout);

//ADD compativilidad VPI viejo FIN
//ADD Fidelidad FIN

/**
* Env�a el comando para obtener un registro de la tabla de planes del POS y espera la 
* respuesta de la misma en forma sincr�nica. Para obtener todos los registros se debe
* hacer un ciclo desde 0 hasta que el c�digo de respuesta sea distinto de VPI_MORE_REC.
* La aplicaci�n queda esperando hasta tenga la respuesta o bien expire el timeout 
* especificado. El puerto debe estar abierto para que la ejecuci�n sea exitosa.
*
* @param index Indice del registro a obtener.
* @param output Estructura con los datos del plan. Se completa dentro de la funci�n.
*
* @return 	VPI_OK
* @return 	VPI_MORE_REC
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD 
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_INDEX
*/
WORD __stdcall vpiGetVersion(vpiVersionOut_t* output);

/**
* Env�a el comando para obtener el PAN y los ultimos 4 digitos de la tarjeta.
* El puerto debe estar abierto para que la ejecuci�n sea exitosa.
*
* @param ninguno.
* @param output Estructura con los datos del PAN, los ultimos 4 digitos de la tarjeta
* y el numero de terminal. Se completa dentro de la funci�n.
*
* @return 	VPI_OK
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
*/
WORD __stdcall vpiGetPANData(vpiPriOut* output);

/**
* Env�a la orden de obtener un determinado registro, con los totales por tarjeta
* del �ltimo cierre realizado con grupo y espera la respuesta de la misma en forma
* sincr�nica.Para obtener todos los registros se debe hacer un ciclo desde 0
* hasta que el c�digo de respuesta sea distinto de VPI_MORE_REC. La aplicaci�n queda esperando
* hasta tenga la respuesta o bien expire el timeout especificado. El puerto debe
* estar abierto para que la ejecuci�n sea exitosa.
*
* @param index Indice del registro que deseo recuperar
* @param output Estructura con la informaci�n del registro que quiero.
*
* @return VPI_OK Fin de registros.
* @return VPI_MORE_REC Quedan registros.
* @return VPI_FAIL No se pudo enviar el comando
* @return VPI_TIMEOUT_EXP Timeout de respuesta expirado sin respuesta.
* @return VPI_INVALID_INDEX El indice del registro no existe.
* @return VPI_TRX_CANCELED Transacci�n cancelada por el usuario.
* @return VPI_INVALID_TRX No se realizo el cierre.
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_LEN
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_INVALID_OUT_LEN
* @return VPI_INVALID_OUT_PARAM
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall vpiGetBatchCloseDataGroup(WORD index, vpiBatchCloseDataGroupOut_t* output);

/*--------------------------(NUEVOS) METODOS CLASICOS --------------------------*/

/**
* Abre el puerto serial de comunicaciones para poder enviar y recibir
* los comandos.El puerto debe estar cerrado para que la ejecuci�n sea
* exitosa.Es necesario para ejecutar el resto de los comandos.
* @param params Par�metros de configuracion del puerto serial.
*
* @return VPI_OK Puerto abierto exitosamente
* @return VPI_FAIL El puerto se encontraba abierto o no se pudo abrir.
*/
WORD __stdcall cmdOpenPort(comParams_t* params);

/**
* Cierra el puerto serial de comunicaciones y lo deja libre para otras
* aplicaciones. El puerto debe estar abierto para que la ejecuci�n sea
* exitosa.Luego de ejecutar este comando, no se puede ejecutar ningun
* otro comando.
* @return VPI_OK Puerto cerrado exitosamente
* @return VPI_FAIL El puerto no se encontraba abierto o no se pudo cerrar.
*/
WORD __stdcall cmdClosePort(void);

/**
* Env�a un mensaje por el puerto y espera la respuesta al mismo en forma
* sincr�nica, para verificar que la conexi�n con el POS est� OK.La
* aplicaci�n queda esperando hasta tenga la respuesta o bien expire el
* timeout default. El puerto debe estar abierto para que la ejecuci�n sea exitosa.
*
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK Conexi�n exitosa.
* @return VPI_FAIL No se pudo enviar el comando posiblemente el puerto est� cerrado.
* @return VPI_TIMEOUT_EXP Timeout de respuesta expirado sin respuesta.
*/
WORD __stdcall cmdTestConnection(SHORT timeout);

/**
* Env�a la orden de realizar una venta y espera la respuesta de la misma en forma
* sincr�nica.La aplicaci�n queda esperando hasta tenga la respuesta o bien expire
* el timeout especificado.El puerto debe estar abierto para que la ejecuci�n sea
* exitosa.
*
* @param input Estructura con los datos de entrada de la venta.
* @param output Estructura con los datos de respuesta de la venta. Se completa dentro de la funci�n.
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK
* @return VPI_FAIL
* @return VPI_TIMEOUT_EXP
* @return VPI_INVALID_ISSUER
* @return VPI_INVALID_PLAN
* @return VPI_TRX_CANCELED
* @return VPI_DIF_CARD
* @return VPI_INVALID_CARD
* @return VPI_EXPIRED_CARD
* @return VPI_ERR_COM
* @return VPI_ERR_PRINT
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall cmdPurchase(vpiPurchaseIn_t* input, vpiTrxOut_t* output, SHORT timeout);

/**
* Env�a la orden de realizar una venta y espera la respuesta de la misma en forma
* sincr�nica.La aplicaci�n queda esperando hasta tenga la respuesta o bien expire
* el timeout especificado.El puerto debe estar abierto para que la ejecuci�n sea
* exitosa.
*
* @param input Estructura con los datos de entrada de la venta.
* @param output Estructura con los datos de respuesta de la venta. Se completa dentro de la funci�n
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK
* @return VPI_FAIL
* @return VPI_TIMEOUT_EXP
* @return VPI_INVALID_ISSUER
* @return VPI_INVALID_PLAN
* @return VPI_TRX_CANCELED
* @return VPI_DIF_CARD
* @return VPI_INVALID_CARD
* @return VPI_EXPIRED_CARD
* @return VPI_ERR_COM
* @return VPI_ERR_PRINT
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall cmdVoid(vpiVoidIn_t* input, vpiTrxOut_t* output, SHORT timeout);

/**
* Env�a la orden de realizar una devoluci�n y espera la respuesta de la misma en
* forma sincr�nica.La aplicaci�n queda esperando hasta tenga la respuesta o bien
* expire el timeout especificado.El puerto debe estar abierto para que la ejecuci�n
* sea exitosa.
*
* @param input Estructura con los datos de entrada de la devoluci�n.
* @param output Estructura con los datos de respuesta de la devoluci�n. Se completa dentro de la funci�n.
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK Conexi�n exitosa.
* @return VPI_FAIL No se pudo enviar el comando.
* @return VPI_TIMEOUT_EXP Timeout de respuesta expirado sin respuesta.
* @return VPI_INVALID_ISSUER El c�digo de tarjeta no existe.
* @return VPI_INVALID_PLAN El c�digo de plan no existe.
* @return VPI_TRX_CANCELED Transacci�n cancelada por el usuario.
* @return VPI_DIF_CARD La tarjeta deslizada por el usuario no coincide con la pedida.
* @return VPI_INVALID_CARD La tarjeta deslizada no es v�lida.
* @return VPI_EXPIRED_CARD La tarjeta deslizada est� vencida.
* @return VPI_ERR_COM El POS no pudo comunicarse con el host.
* @return VPI_ERR_PRINT El POS no pudo imprimir el ticket.
* @return VPI_INVALID_IN_CMD Nombre del comando inexistente.
* @return VPI_INVALID_IN_LEN Largo de los par�metros inv�lido para este comando.
* @return VPI_INVALID_IN_PARAM Formato de alg�n par�metro no es correcto.
* @return VPI_INVALID_OUT_CMD Nombre del comando devuelto no coincide con el enviado.
* @return VPI_INVALID_OUT_LEN Largo de los par�metros devueltos inv�lido para este comando.
* @return VPI_INVALID_OUT_PARAM Formato de alg�n par�metro devuelto no es correcto.
* @return VPI_GENERAL_FAIL Error general en la operaci�n.
*/
WORD __stdcall cmdRefund(vpiRefundIn_t* input, vpiTrxOut_t* output, SHORT timeout);

/**
* Env�a la orden de realizar una anulaci�n de devoluci�n y espera la respuesta
* de la misma en forma sincr�nica.La aplicaci�n queda esperando hasta tenga la
* respuesta o bien expire el timeout especificado.El puerto debe estar abierto
* para que la ejecuci�n sea exitosa.
*
* @param input Estructura con los datos de entrada de la anulaci�n.
* @param output Estructura con los datos de respuesta de la anulaci�n. Se completa dentro de la funci�n.
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return 	VPI_OK
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_ISSUER
* @return 	VPI_INVALID_TICKET
* @return 	VPI_EMPTY_BATCH
* @return 	VPI_TRX_CANCELED
* @return 	VPI_DIF_CARD
* @return 	VPI_INVALID_CARD
* @return 	VPI_EXPIRED_CARD
* @return 	VPI_INVALID_TRX
* @return 	VPI_ERR_COM
* @return 	VPI_ERR_PRINT
*/
WORD __stdcall cmdRefundVoid(vpiVoidIn_t* intput, vpiTrxOut_t* output, SHORT timeout);

/**
* Env�a la orden de realizar un cierre de lote. La aplicaci�n queda esperando hasta
* tenga la respuesta o bien expire el timeout especificado. El puerto debe estar
* abierto para que la ejecuci�n sea exitosa.
*
* @param output Estructura con el resultado de la operaci�n contra el host. Se completa dentro de la funci�n.
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return 	VPI_OK
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_TRX_CANCELED
* @return 	VPI_ERR_COM
* @return 	VPI_ERR_PRINT
*/
WORD __stdcall cmdBatchClose(vpiBatchCloseOut_t* output, SHORT timeout);

/**
* Env�a la orden de obtener la informaci�n de la �ltima transacci�n realizada
* y espera la respuesta de la misma en forma sincr�nica.La aplicaci�n queda
* esperando hasta tenga la respuesta o bien expire el timeout especificado.
* El puerto debe estar abierto para que la ejecuci�n sea exitosa.
* @param trxCode C�digo del tipo de transacci�n: VPI_PURCHASE, VPI_VOID,
VPI_REFUND, VPI_REFUND_VOID
*
* @param output  Estructura con los datos de respuesta de la �ltima transacci�n realizada.
*				 Se completa dentro de la funci�n.
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return 	VPI_OK
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_PARAM
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_ISSUER
* @return 	VPI_INVALID_TICKET
* @return 	VPI_INVALID_PLAN
* @return 	VPI_EMPTY_BATCH
* @return 	VPI_TRX_CANCELED
* @return 	VPI_DIF_CARD
* @return 	VPI_INVALID_CARD
* @return 	VPI_EXPIRED_CARD
* @return 	VPI_ERR_COM
* @return 	VPI_ERR_PRINT
*/
WORD __stdcall cmdGetLastTrxData(WORD* trxCode, vpiTrxOut_t* output, SHORT timeout);

/**
* Env�a la orden de obtener un determinado registro, con los totales por tarjeta
* del �ltimo cierre realizado y espera la respuesta de la misma en forma
* sincr�nica.Para obtener todos los registros se debe hacer un ciclo desde 0
* hasta que el c�digo de respuesta sea distinto de VPI_MORE_REC. La aplicaci�n queda esperando
* hasta tenga la respuesta o bien expire el timeout especificado. El puerto debe
* estar abierto para que la ejecuci�n sea exitosa.
*
* @param index Indice del registro que deseo recuperar
* @param output Estructura con la informaci�n del registro que quiero.
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return VPI_OK Fin de registros.
* @return VPI_MORE_REC Quedan registros.
* @return VPI_FAIL No se pudo enviar el comando
* @return VPI_TIMEOUT_EXP Timeout de respuesta expirado sin respuesta.
* @return VPI_INVALID_INDEX El indice del registro no existe.
* @return VPI_TRX_CANCELED Transacci�n cancelada por el usuario.
* @return VPI_INVALID_TRX No se realizo el cierre.
* @return VPI_INVALID_IN_CMD
* @return VPI_INVALID_IN_LEN
* @return VPI_INVALID_IN_PARAM
* @return VPI_INVALID_OUT_CMD
* @return VPI_INVALID_OUT_LEN
* @return VPI_INVALID_OUT_PARAM
* @return VPI_GENERAL_FAIL
*/
WORD __stdcall cmdGetBatchCloseData(WORD index, vpiBatchCloseDataOut_t* output, SHORT timeout);

/**
* Env�a la orden de re-imprimir el ticket de la �ltima transacci�n.La aplicaci�n queda
* esperando hasta tenga la respuesta o bien expire el timeout default.El puerto debe
* estar abierto para que la ejecuci�n sea exitosa.
*
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return 	VPI_OK
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_PARAM
* @return 	VPI_GENERAL_FAIL
*/
WORD __stdcall cmdPrintTicket(SHORT timeout);

/**
* Env�a la orden de re-imprimir el ticket del �ltimo cierre de lote. La aplicaci�n queda
* esperando hasta tenga la respuesta o bien expire el timeout default.El puerto debe estar
* abierto para que la ejecuci�n sea exitosa.
*
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return 	VPI_OK
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_PARAM
* @return 	VPI_GENERAL_FAIL
*/
WORD __stdcall cmdPrintBatchClose(SHORT timeout);

/**
* Env�a el comando para obtener un registro de la tabla de tarjetas del POS y espera
* la respuesta de la misma en forma sincr�nica. Para obtener todos los registros se
* debe hacer un ciclo desde 0 hasta que el c�digo de respuesta sea distinto de VPI_MORE_REC.
* La aplicaci�n queda  esperando hasta tenga la respuesta o bien expire el timeout especificado.
* El puerto debe estar abierto para que la ejecuci�n sea exitosa.
*
* @param index Indice del registro a obtener.
* @param output Estructura con los datos de la tarjeta. Se completa dentro de la funci�n.
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return 	VPI_OK
* @return 	VPI_MORE_REC
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_INDEX
*/
WORD __stdcall cmdGetIssuer(WORD index, vpiIssuerOut_t* output, SHORT timeout);

/**
* Env�a el comando para obtener un registro de la tabla de planes del POS y espera la
* respuesta de la misma en forma sincr�nica. Para obtener todos los registros se debe
* hacer un ciclo desde 0 hasta que el c�digo de respuesta sea distinto de VPI_MORE_REC.
* La aplicaci�n queda esperando hasta tenga la respuesta o bien expire el timeout
* especificado. El puerto debe estar abierto para que la ejecuci�n sea exitosa.
*
* @param index Indice del registro a obtener.
* @param output Estructura con los datos del plan. Se completa dentro de la funci�n.
* @param timeout Tiempo de espera de respuesta en segundos.
*
* @return 	VPI_OK
* @return 	VPI_MORE_REC
* @return 	VPI_FAIL
* @return 	VPI_TIMEOUT_EXP
* @return 	VPI_INVALID_IN_CMD
* @return 	VPI_INVALID_IN_PARAM
* @return 	VPI_INVALID_OUT_CMD
* @return 	VPI_GENERAL_FAIL
* @return 	VPI_INVALID_INDEX
*/
WORD __stdcall cmdGetPlan(WORD index, vpiPlanOut_t* output, SHORT timeout);

/**
* Env�a el comando para setear un timeout global de respuesta al POS; permitiendo de esta 
* forma ajustar el valor del timeout de respuesta por defecto del POS seg�n las necesidades 
* y caracter�sticas tanto del POS como la aplicaci�n del integrador.
*
* @param timeout Tiempo de espera por defecto de las futuras respuestas, en segundos.
*/
WORD __stdcall cmdSetTimeout(SHORT timeout);

#endif //_VPIPC_H_