package application;

import java.io.PrintWriter;
import com.fazecast.jSerialComm.SerialPort;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyCodeCombination;
import javafx.scene.input.KeyCombination;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

public class Controle extends Application {
	private SerialPort porta;
	public Controle(Stage stage, SerialPort porta) {
		this.porta=porta;
		try {
			start(stage);
		} catch (Exception e) {
			System.err.println("Falha na execução da janela Controle\n\n"+e);
		}
	}
	@Override
	public void start(Stage primaryStage) throws Exception {
		AnchorPane root = new AnchorPane();
		PrintWriter output = new PrintWriter(porta.getOutputStream());
		
		Button btnCima = new Button();
		Image image = new Image(getClass().getResourceAsStream("cima.png"));
		btnCima.setGraphic(new ImageView(image));
        AnchorPane.setTopAnchor(btnCima,230.0);
        AnchorPane.setRightAnchor(btnCima, 210.0);
        AnchorPane.setLeftAnchor(btnCima, 210.0);
        btnCima.setOnAction(event -> {
        	 output.print(1);
             output.flush();
             System.out.println("Frente pressionado");
        });
        btnCima.setOnKeyPressed(event->{
        	KeyCombination UP = new KeyCodeCombination(KeyCode.UP);
        	if(UP.match(event)) {
        		output.print(1);
                output.flush();
                System.out.println("Frente pressionado");
        	}
        });
        
		Button btnBaixo = new Button();
		Image imgBaixo = new Image(getClass().getResourceAsStream("baixo.png"));
		btnBaixo.setGraphic(new ImageView(imgBaixo));
		AnchorPane.setTopAnchor(btnBaixo,320.0);
        AnchorPane.setRightAnchor(btnBaixo, 210.0);
        AnchorPane.setLeftAnchor(btnBaixo, 210.0);
        btnBaixo.setOnAction(event->{
        	output.print(2);
            output.flush();
            System.out.println("Trás pressionado");
        });
        btnBaixo.setOnKeyPressed(event->{
        	KeyCombination DOWN = new KeyCodeCombination(KeyCode.DOWN);
        	if(DOWN.match(event)) {
        		output.print(2);
                output.flush();
                System.out.println("Trás pressionado");
        	}
        });
        
        Button btnEsq = new Button();
		Image imgbtnEsq = new Image(getClass().getResourceAsStream("esquerda.png"));
		btnEsq.setGraphic(new ImageView(imgbtnEsq));
		AnchorPane.setTopAnchor(btnEsq,320.0);
        AnchorPane.setRightAnchor(btnEsq, 300.0);
        AnchorPane.setLeftAnchor(btnEsq, 120.0);
        btnEsq.setOnAction(event->{
        	output.print(3);
            output.flush();
            System.out.println("Esquerda pressionado");
        });
        btnEsq.setOnKeyPressed(event->{
        	KeyCombination LEFT = new KeyCodeCombination(KeyCode.LEFT);
        	if(LEFT.match(event)) {
        		output.print(3);
                output.flush();
                System.out.println("Esquerda pressionado");
        	}
        });
        
        Button btnDir = new Button();
		Image imgbtnDir = new Image(getClass().getResourceAsStream("direita.png"));
		btnDir.setGraphic(new ImageView(imgbtnDir));
		AnchorPane.setTopAnchor(btnDir,320.0);
        AnchorPane.setRightAnchor(btnDir, 120.0);
        AnchorPane.setLeftAnchor(btnDir, 300.0);
        btnDir.setOnAction(event->{
        	output.print(4);
            output.flush();
            System.out.println("Direita pressionado");
        });
        btnDir.setOnKeyPressed(event->{
        	KeyCombination RIGHT = new KeyCodeCombination(KeyCode.RIGHT);
        	if(RIGHT.match(event)) {
        		output.print(4);
                output.flush();
                System.out.println("Direita pressionado");
        	}
        });
        
		root.getChildren().addAll(btnCima,btnBaixo,btnEsq,btnDir);
		
		if(btnCima.isPressed()){
           
        }else if(btnBaixo.isPressed()) {
        	output.print(2);
            output.flush();
        }else if(btnDir.isPressed()) {
        	output.print(4);
            output.flush();
        }else if(btnEsq.isPressed()) {
        	output.print(3);
            output.flush();
        }else {
        	output.print(0);
            output.flush();
        }
		
		Scene scene = new Scene(root,500,440);
		primaryStage.setTitle("Controle AVATAR®");
		primaryStage.setScene(scene);
		primaryStage.show();
	}
	

	public static void begin(String[] args){
		launch(args);

	}

}
