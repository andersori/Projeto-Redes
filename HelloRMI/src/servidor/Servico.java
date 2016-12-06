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
//Inteface utilizada pelo servidor e pelo cliente
public interface Servico extends Remote{
    public double logaritimo(double num) throws RemoteException;
    public double raiz(double num) throws RemoteException;
    public int soma(int a, int b) throws RemoteException;  
}
