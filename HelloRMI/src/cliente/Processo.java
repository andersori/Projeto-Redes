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
    private int[] vetor;
    private int inicio;
    private int fim;
    
    public Processo(){
        setServico();
    }

    public Processo(int[] vetor) {
        this();
        this.vetor = vetor;
    }
    
    public Processo(int[] vetor, int inicio, int fim){
        this(vetor);
        setInicio(inicio);
        setFim(fim);
    }

    public int[] getVetor() {
        return vetor;
    }

    public void setVetor(int[] vetor) {
        this.vetor = vetor;
    }

    public int getInicio() {
        return inicio;
    }

    public void setInicio(int inicio) {
        this.inicio = inicio;
    }

    public int getFim() {
        return fim;
    }

    public void setFim(int fim) {
        this.fim = fim;
    }
    
    public Servico getServico() {
        return servico;
    }

    private void setServico() {
        try {
            //Retorna uma referência, um stub, para o objeto remoto associado ao nome especificado.
            this.servico = (Servico) Naming.lookup("rmi://localhost:52101/coisa");
            
        } catch (NotBoundException | MalformedURLException | RemoteException ex) {
            Logger.getLogger(Processo.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    
    @Override
    public void run() {
        for(int i = inicio; i < fim; i++){
            int valor = vetor[i];
            try {
                //Chamando o serviço que o servidor disponibiliza
                vetor[i] = servico.soma(valor, valor);
                
            } catch (RemoteException ex) {
                Logger.getLogger(Processo.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
    
}
