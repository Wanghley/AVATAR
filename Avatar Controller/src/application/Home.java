/**
 * 
 */
package application;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

/**
 * @author Wanghley Soares Martins - Projeto AVATAR®
 * @version 1.0 - Beta
 * @since 2019
 * @
 */
public class Home extends Application{

	@Override
	public void start(Stage primaryStage) throws Exception {
		AnchorPane root = new AnchorPane();
		
		Scene scene = new Scene(root,900,450);
		primaryStage.setScene(scene);
		primaryStage.setTitle("AVATAR® Controller");
		primaryStage.setResizable(false);
		primaryStage.show();
	}
	
	public static void main(String[] args) {

	}

}
