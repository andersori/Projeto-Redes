/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cliente;

import java.util.Random;


/**
 *
 * @author Anderson
 */
public class MainCliente {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
            
        int vetor[] = new int[108];
        Random r = new Random();
        
        for(int i = 0; i < 108; i++){
            vetor[i] = r.nextInt() * 1021;
        }
        
        int n = 8;
        
        int intervalo = 108 / n;
        int resto = (108 % n) * n;
        int inicio = 0;
        int fim = intervalo;
        
        for(int i = 0; i < n; i++){
            Thread t = new Thread(new Processo(vetor, inicio, fim));
            inicio = fim;
            
            if( i == n -1){
                fim = fim + intervalo + resto;
            }
            else{
                fim = fim + intervalo;
            }
            
            
            t.start();
        }

    }
    
}
