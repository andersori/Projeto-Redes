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
public class ServicoImplementado extends UnicastRemoteObject implements Servico{

    public ServicoImplementado() throws RemoteException{
        super();
    }

    @Override
    public int logaritimo() throws RemoteException {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public int potencia() throws RemoteException {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public int soma(int a, int b) throws RemoteException {
        return a + b;
    }
       
}
