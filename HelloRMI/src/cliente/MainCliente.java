/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package cliente;

import java.util.Random;
import java.util.Scanner;
/**
 *
 * @author Anderson
 */
public class MainCliente {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
            
        int vetor[] =  new int[108];
        int n;
        
        Random r = new Random();
        for(int i = 0; i < 108; i++){
            int valor = r.nextInt(150);
            vetor[i] = valor;
        }
        
        System.out.println("Qantidade de Threads");
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        
        int inicio = 0;
        int fim = 0;
        int intervalo = 108 / n;
        //Falta definir esse intervalo
        
        long tempoInicial = System.currentTimeMillis();
        for(int i = 0; i < n; i++){
            Thread t = new Thread(new Processo(vetor, inicio, fim));
            t.start();
        }
        System.out.println("Tempo decorrido: " + (System.currentTimeMillis() - tempoInicial) + " milisegundos.");
    }
    
}
