import java.util.ArrayList;
import java.util.List;

class Cajero {

    private boolean atendido=false;
    private int numCaj;

    public Cajero(int numCaj) {
        this.numCaj = numCaj;
    }
    
    
    synchronized boolean atenderCliente (int numcli){
        Cliente cli=new Cliente(null, numcli); 
        boolean prueba = cli.getListo();
        
        try {
            if (atendido==false && prueba==false) {
                atendido=true;
                System.out.println("Caja "+numCaj+" atendiendo al cliente "+numcli);
                Thread.sleep(2000);
                System.out.println("Caja "+numCaj+" terminó con el cliente "+numcli);
                atendido=false;
                cli.setListo(true);
                return atendido;
            }else {
                return true;
            }
        }
        catch (InterruptedException e) {
            e.printStackTrace();
            return false;
        }
    }
}

class Cliente extends Thread {
    List<Cajero> cajas;
    int numeroCliente;
    private boolean listo=false;

    Cliente (List<Cajero> cajas, int numeroCliente){
        this.cajas = cajas;
        this.numeroCliente=numeroCliente;
    }

    public int getNumeroCliente() {
        return numeroCliente;
    }

    public boolean getListo() {
        return listo;
    }

    public void setListo(boolean listo) {
        this.listo = listo;
    }

    public void run(){
        boolean atendido = false;
        while (atendido==false){
            for (int i=0; i<cajas.size(); i++){ // recorrer las cajas y pruebo si estan ocupadas
                atendido = cajas.get(i).atenderCliente(getNumeroCliente());
                if (atendido==true){
                    break;
                }
            }
            try { 
                Thread.sleep(100); 
            } catch (Exception e) {}
            
        }
    }
}

public class Supermercado3 {
    public static void main(String[] args) throws InterruptedException {


        List<Cajero> cajas = new ArrayList<>();
        for (int index = 0; index < 3; index++) {
            cajas.add(new Cajero(index+1));
        }
        

        List<Cliente> d = new ArrayList<>();
        for (int i = 0; i < 7; i++) {
            d.add(new Cliente( cajas, i+1));
            d.get(i).start();
            
        }

        for (Cliente c : d) {
            try { 
                c.join(); 
            }
            catch (InterruptedException e) {}
        }
        
    }
}
