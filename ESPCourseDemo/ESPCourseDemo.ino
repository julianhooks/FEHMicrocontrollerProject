//AT //Basic check
//ATE0 // Turn echo off
//AT+CWMODE=1 //Set ESP to client mode
//AT+CWJAP="Test","" //Connect to Local netowrk
//WAit until Got IP
//AT+CIFSR //Get Local IP
//AT+PING="#.#.0.1" //based on response from CIFSR
//AT+CIPSTART="TCP","#.#.0.1",port# //Open connection to server
//AT+CIPSEND=length of HTTP request
// //HTTP Requests are hard