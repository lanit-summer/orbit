package orbit;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.BorderPane;
import javafx.stage.Stage;

public class MainApp extends Application {
	static {
	    try {
	     System.loadLibrary("orbit");
	    } catch (UnsatisfiedLinkError e) {
	      System.err.println("Native code library failed to load. " + e);
	      System.exit(1);
	    }
	  }

	private Stage primaryStage;
	private BorderPane rootLayout;

	@Override
	public void start(Stage primaryStage) {
		this.primaryStage = primaryStage;
		this.primaryStage.setTitle("ORBIT GAME");
		initLayout();
	}

	public void initLayout(){
		try {
			FXMLLoader loader = new FXMLLoader();
			loader.setLocation(MainApp.class.getResource("view/RootLayout.fxml"));
			rootLayout = (BorderPane) loader.load();

			Scene scene = new Scene(rootLayout);
			primaryStage.setScene(scene);
			primaryStage.show();

			loader = new FXMLLoader();
            loader.setLocation(MainApp.class.getResource("view/GameInput.fxml"));
            AnchorPane gameInput = (AnchorPane) loader.load();
            rootLayout.setCenter(gameInput);
		}
		catch (Exception e){
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {
		launch(args);
	}
}
