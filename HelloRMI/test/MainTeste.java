/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Anderson
 */
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

public class MainTeste {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws InterruptedException {
        BlockingQueue vetor = new ArrayBlockingQueue<Integer>(108);
        
        int i = (int) vetor.take();
    }
    
}
