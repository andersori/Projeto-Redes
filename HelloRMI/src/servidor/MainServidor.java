/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package servidor;

import java.net.MalformedURLException;
import java.rmi.AlreadyBoundException;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Anderson
 */
public class MainServidor {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        try {
            //Cria e exporta uma instância de registro no host local que aceita solicitações na porta especificada.
            LocateRegistry.createRegistry(52101);
            
            //Liga o nome especificado a um objeto remoto.
            Naming.bind("rmi://localhost:52101/coisa", new ServicoImplementado());
            
            System.out.println("Servidor funcionando.");
            
        } catch (AlreadyBoundException | MalformedURLException | RemoteException ex) {
            Logger.getLogger(MainServidor.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
}
