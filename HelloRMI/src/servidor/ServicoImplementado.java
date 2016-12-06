/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package servidor;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

/**
 *
 * @author Anderson
 */
//Implementação dos metosdos da interface
public class ServicoImplementado extends UnicastRemoteObject implements Servico{

    public ServicoImplementado() throws RemoteException{
        super();
    }

    @Override
    public double logaritimo(double num) throws RemoteException {
        return Math.log(num);
    }

    @Override
    public double raiz(double num) throws RemoteException {
        return Math.sqrt(num);
    }

    @Override
    public int soma(int a, int b) throws RemoteException {
        return a + b;
    }
       
}
