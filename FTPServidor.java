import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Scanner;

import org.apache.commons.net.ftp.FTP;
import org.apache.commons.net.ftp.FTPClient;
import org.apache.commons.net.ftp.FTPFile;
import org.apache.commons.net.ftp.FTPReply;

public class FTPServidor {
    static Scanner sc = new Scanner(System.in);
    public static void main(String[] args) {
        FTPClient cliente = new FTPClient();
        
        
        try {
            cliente.connect("192.168.204.106");
            cliente.enterLocalPassiveMode(); 
            if (cliente.login("profesor", "123")) {
                System.out.println("Login correcto...");
            }

            String comando = "";
            while (!comando.equals("quit")) {
                System.out.print("ftp> ");
                comando = sc.nextLine();
                String[] partes = comando.split(" ");

                switch (partes[0]) {
                    case "ls":
                        listarDirectorio(cliente, partes.length > 1 ? partes[1] : ".");
                        verificarRespuesta(cliente);
                        break;
                    case "put":
                        subirFichero(cliente, partes[1], partes[2]);
                        verificarRespuesta(cliente);
                        break;
                    case "get":
                        obtenerFichero(cliente, partes[1], partes[2], sc);
                        verificarRespuesta(cliente);
                        break;
                    case "mkdir":
                        cliente.makeDirectory(partes[1]);
                        verificarRespuesta(cliente);
                        break;
                    case "rename":
                        renombrarFichero(cliente, partes[1], partes[2]);
                        verificarRespuesta(cliente);
                        break;
                    case "mode":
                        if (partes[1].equalsIgnoreCase("pasv")) {
                            cliente.enterLocalPassiveMode();
                            System.out.println("Modo Pasivo activado.");
                        } else {
                            cliente.enterLocalActiveMode();
                            System.out.println("Modo Activo activado.");
                        }
                        verificarRespuesta(cliente);
                        break;
                    case "mput":
                        for (int i = 1; i < partes.length; i++) {
                            new Thread(new TareaSubida("192.168.204.106", "profesor", "123", partes[i], partes[i])).start();
                        }
                        verificarRespuesta(cliente);
                        break;
                }
            }
            cliente.logout();
            cliente.disconnect();
        } catch (IOException e) { e.printStackTrace(); }
    }

    private static void listarDirectorio(FTPClient cliente, String ruta) throws IOException {
        FTPFile[] files = cliente.listFiles(ruta);
        for (FTPFile f : files) {
            String tipo = f.isDirectory() ? "[DIR]" : "[FILE]";
            System.out.println(tipo + " " + f.getName() + " - " + f.getSize() + " bytes");
        }
    }


    private static void subirFichero(FTPClient cliente, String rutaLocal, String rutaRemota) throws IOException {
        cliente.setFileType(FTP.BINARY_FILE_TYPE); // Siempre modo binario como hablamos antes
        BufferedInputStream in = new BufferedInputStream(new FileInputStream(rutaLocal));
        
        if (cliente.storeFile(rutaRemota, in)) {
            System.out.println("Subida con éxito.");
        }
        in.close();
    }

    private static void obtenerFichero(FTPClient cliente, String rutaRemota, String rutaLocal, Scanner sc) throws IOException {
        File localFile = new File(rutaLocal);
        if (localFile.exists()) {
            System.out.print("El archivo ya existe. ¿Sobrescribir? (s/n): ");
            String resp = sc.nextLine();
            if (!resp.equalsIgnoreCase("s")) return; 
        }

        cliente.setFileType(FTP.BINARY_FILE_TYPE);

        BufferedOutputStream out = new BufferedOutputStream(new FileOutputStream(rutaLocal));
        
        if (cliente.retrieveFile(rutaRemota, out)) {
            System.out.println("Descarga completada.");
        }
        out.close();
    }

    private static void renombrarFichero(FTPClient cliente, String origen, String destino) throws IOException {
        boolean exito = cliente.rename(origen, destino);
        if (exito) {
            System.out.println("Cambiado: " + origen + " -> " + destino);
        } else {
            System.out.println("Error al renombrar. Comprueba que el origen existe.");
        }
    }

    private static void verificarRespuesta(FTPClient cliente) {
        int codigo = cliente.getReplyCode();
        String respuesta = cliente.getReplyString();
        
        // Basado en tu ClienteFTP1.java
        if (FTPReply.isPositiveCompletion(codigo)) {
            System.out.println("Operación exitosa [" + codigo + "]: " + respuesta);
        } else {
            System.out.println("Aviso/Error [" + codigo + "]: " + respuesta);
        }
    }
}

class TareaSubida implements Runnable {
    private String host, user, pass, local, remoto;
    public TareaSubida(String h, String u, String p, String l, String r) {
        this.host = h; this.user = u; this.pass = p; this.local = l; this.remoto = r;
    }

    @Override
    public void run() {
        FTPClient c = new FTPClient();
        try {
            c.connect(host);
            c.login(user, pass);
            c.enterLocalPassiveMode();
            c.setFileType(FTP.BINARY_FILE_TYPE);
            File f = new File(local);
            if(f.exists()){
                try (BufferedInputStream in = new BufferedInputStream(new FileInputStream(f))) {
                    if (c.storeFile(remoto, in)) {
                        System.out.println("\n[HILO MPUT] Finalizado: " + remoto);
                    }
                }
            }
            c.logout();
            c.disconnect();
        } catch (IOException e) { System.out.println("Error en hilo: " + e.getMessage()); }
    }
}