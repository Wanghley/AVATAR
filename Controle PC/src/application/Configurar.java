package application;

import com.fazecast.jSerialComm.SerialPort;

import javafx.application.Application;
import javafx.concurrent.Service;
import javafx.concurrent.Task;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.layout.AnchorPane;


public class Configurar extends Application {
	private static ComboBox<String> cbPortas = new ComboBox<String>();
	private static SerialPort porta;

	@Override
	public void start(Stage primaryStage) {
		AnchorPane root = new AnchorPane();

		Label lblPort = new Label("Selecione a porta:");
		AnchorPane.setTopAnchor(lblPort, 10.0);
		AnchorPane.setRightAnchor(lblPort, 50.0);
		AnchorPane.setLeftAnchor(lblPort, 95.0);

		AnchorPane.setTopAnchor(cbPortas, 40.0);
		AnchorPane.setRightAnchor(cbPortas, 65.0);
		AnchorPane.setLeftAnchor(cbPortas, 65.0);

		Button btnIniciar = new Button();
		btnIniciar.setText("Iniciar Controle");
		AnchorPane.setTopAnchor(btnIniciar, 150.0);
		AnchorPane.setRightAnchor(btnIniciar, 50.0);
		AnchorPane.setLeftAnchor(btnIniciar, 50.0);
		btnIniciar.setDisable(true);
		btnIniciar.setOnAction(event->{
			primaryStage.close();
			Controle controle = new Controle(new Stage(),porta);
		});
		
		Button btnConectar = new Button();
		btnConectar.setText("Conectar");
		AnchorPane.setTopAnchor(btnConectar, 100.0);
		AnchorPane.setRightAnchor(btnConectar, 50.0);
		AnchorPane.setLeftAnchor(btnConectar, 50.0);
		btnConectar.setOnAction(event->{
			if(btnConectar.getText().equals("Conectar")){
	            porta=SerialPort.getCommPort(cbPortas.getSelectionModel().getSelectedItem().toString());
	            if(porta.openPort()){
	                btnConectar.setText("Desconectar");
	                btnIniciar.setDisable(false);
	                cbPortas.setDisable(true);
	            }
	        }else{
	            porta.closePort();
	            cbPortas.setDisable(false);
	            btnIniciar.setDisable(true);
	            btnConectar.setText("conectar");
	        }

		});

		root.getChildren().addAll(lblPort,cbPortas,btnConectar,btnIniciar);		

		Scene scene = new Scene(root,320,220);
		primaryStage.setTitle("Configurações AVATAR®");
		primaryStage.setScene(scene);
		primaryStage.show();
	}

	public static void main(String[] args) {
		Service<Void> service = new Service<Void>() {
	        @Override
	        protected Task<Void> createTask() {
	            return new Task<Void>() {           
	                @Override
	                protected Void call() throws Exception {
	                    //Background work                       
	                	SerialPort[] portNames = SerialPort.getCommPorts();
	            		for(SerialPort portName:portNames){
	            			cbPortas.getItems().add(portName.getSystemPortName());
	            		}
	     
	                    return null;
	                }
	            };
	        }
	    };
	    service.start();
		
		launch(args);
		
	}
}
