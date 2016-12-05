/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package servidor;

import java.rmi.Remote;
import java.rmi.RemoteException;

/**
 *
 * @author Anderson
 */
public interface Servico extends Remote{
    public int logaritimo() throws RemoteException;
    public int potencia() throws RemoteException;
    public int soma(int a, int b) throws RemoteException;  
}
