/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cliente;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.util.logging.Level;
import java.util.logging.Logger;
import servidor.Servico;

/**
 *
 * @author Anderson
 */
public class Processo implements Runnable{
    private Servico servico;
    private int vetor[];
    private int posInicio;
    private int posFim;
    
    public Processo(){
        setServico();
    }
    
    public Processo(int vetor[]){
        this();
        setVetor(vetor);
    }
    
    public Processo(int vetor[], int posInicio, int posFim){
        this(vetor);
        setPosInicio(posInicio);
        setPosFim(posFim);
    }

    public Servico getServico() {
        return servico;
    }

    private void setServico() {
        try {
            this.servico = (Servico) Naming.lookup("rmi://localhost:5821/coisa");
            
        } catch (NotBoundException | MalformedURLException | RemoteException ex) {
            Logger.getLogger(Processo.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public int[] getVetor() {
        return vetor;
    }

    public void setVetor(int[] vetor) {
        this.vetor = vetor;
    }

    public int getPosInicio() {
        return posInicio;
    }

    public void setPosInicio(int posInicio) {
        this.posInicio = posInicio;
    }

    public int getPosFim() {
        return posFim;
    }

    public void setPosFim(int posFim) {
        this.posFim = posFim;
    }
    
    
    
    
    @Override
    public void run() {
        try {
            int cont = 0;
            for(int i = this.posInicio; i < this.posFim; i++){
                int valor = vetor[i];
                
                vetor[i] = servico.soma(valor, valor);
                cont++;
            }
            System.out.println("Cont = " + cont + ".");
        } catch (RemoteException ex) {
            Logger.getLogger(Processo.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
}
