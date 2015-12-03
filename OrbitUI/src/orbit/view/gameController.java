package orbit.view;

import javafx.scene.control.Alert;
import javafx.scene.control.TextField;
import javafx.scene.control.TextArea;
import javafx.scene.control.Alert.AlertType;
import javafx.application.Platform;
import javafx.fxml.FXML;
import orbit.model.Ship;
import javafx.application.Platform;
import javafx.stage.DirectoryChooser;
import javafx.stage.Stage;
import javafx.scene.layout.BorderPane;
import javax.xml.bind.JAXBContext;
import javax.xml.bind.Marshaller;
import javax.xml.bind.Unmarshaller;
import java.io.File;

public class gameController {
	@FXML
	private TextField shipEdgeLength;
	@FXML
	private TextField shipMass;
	@FXML
	private TextField fuelMass;
	@FXML
	private TextField maxFuelUsagePerSec;
	@FXML
	private TextField impulsePerFuel;
	@FXML
	private TextField maxOverload;
	@FXML
	private TextField maxHeating;
	@FXML
	private TextField initialX;
	@FXML
	private TextField initialY;
	@FXML
	private TextField initialZ;
	@FXML
	private TextField orientationX;
	@FXML
	private TextField orientationY;
	@FXML
	private TextField orientationZ;
	@FXML
	private TextField rotationX;
	@FXML
	private TextField rotationY;
	@FXML
	private TextField rotationZ;
	@FXML
	private TextField maxRotationX;
	@FXML
	private TextField maxRotationY;
	@FXML
	private TextField maxRotationZ;
	@FXML
	private TextArea commands;
	@FXML
	private TextField quantsize;
	@FXML
	private TextField quantnumber;
	@FXML
	private Stage parent;
	@FXML
	private BorderPane border;
	private Ship ship;
	private Celestia celestia;


	public void handleGetTrajectory(){

		if (isValid()){
			this.ship = new Ship();

			this.ship.setParams(Double.parseDouble(this.shipEdgeLength.getText()),
					Double.parseDouble(this.shipMass.getText()),Double.parseDouble(this.fuelMass.getText()),
					Double.parseDouble(this.maxFuelUsagePerSec.getText()),Double.parseDouble(this.impulsePerFuel.getText()),
					Double.parseDouble(this.maxOverload.getText()),Double.parseDouble(this.maxHeating.getText()));

			this.ship.setInitial(Double.parseDouble(this.initialX.getText()),
				Double.parseDouble(this.initialY.getText()),
				Double.parseDouble(this.initialZ.getText()));

			this.ship.setOrientation(Double.parseDouble(this.orientationX.getText()),
				Double.parseDouble(this.orientationY.getText()),
				Double.parseDouble(this.orientationZ.getText()));

			this.ship.setMaxRotation(Double.parseDouble(this.maxRotationX.getText()),
				Double.parseDouble(this.maxRotationY.getText()),
				Double.parseDouble(this.maxRotationZ.getText()));

			this.ship.setQuants(Integer.parseInt(this.quantsize.getText()), Integer.parseInt(this.quantnumber.getText()));

			this.ship.setFirstSpeed(0.0, 0.0, 0.0);

			if(commands.getText() != null || commands.getText().length() != 0){;
				this.ship.setCommands(commands.getText());
			}
			getCelestiaPath();
			this.ship.setCelestia(celestia);
			this.ship.makeTrajectory();
			Alert alert = new Alert(AlertType.INFORMATION);
	        alert.setTitle("Траетория готова");
	        alert.setHeaderText("Расположена в файле orbit.xyzv");
	        alert.showAndWait();
		}

	}

	public void setCelestiaPath(){
		Stage stage = (Stage) border.getScene().getWindow();
		DirectoryChooser chooser = new DirectoryChooser();
		chooser.setTitle("Путь к Celestia");
		String celPath = chooser.showDialog(stage).getAbsolutePath();
		celestia = new Celestia();
		celestia.setPath(celPath);
		if(System.getProperty("os.name").equals("Linux")){
			celestia.setPathToTrajectory(celPath+"/extras-standard/Orbit-test/data/orbit.xyzv");
		}
		else {
			celestia.setPathToTrajectory(celPath+"/extras/Orbit-test/data/orbit.xyzv");
		}
		try {
			File file = new File("data/settings.xml");
			JAXBContext jaxbContext = JAXBContext.newInstance(Celestia.class);
			Marshaller jaxbMarshaller = jaxbContext.createMarshaller();
			jaxbMarshaller.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, true);
			jaxbMarshaller.marshal(celestia, file);
		}
		catch (Exception e){
			e.printStackTrace();
		}
	}

	public void getCelestiaPath(){
		try {

			File file = new File("data/settings.xml");
			JAXBContext jaxbContext = JAXBContext.newInstance(Celestia.class);

			Unmarshaller jaxbUnmarshaller = jaxbContext.createUnmarshaller();
		    celestia = (Celestia) jaxbUnmarshaller.unmarshal(file);
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

	public void onExit(){
		Platform.exit();
	}

	public void setTest(){
		initialX.setText("0");
		initialY.setText("0");
		initialZ.setText("32650.1");

		orientationX.setText("0");
		orientationY.setText("0");
		orientationZ.setText("1");

		shipEdgeLength.setText("0.001");
		shipMass.setText("3.0");
		fuelMass.setText("10.0");
		maxFuelUsagePerSec.setText("100");
		impulsePerFuel.setText("20");
		maxOverload.setText("200000");
		maxHeating.setText("100000000");

		maxRotationX.setText("10.0");
		maxRotationY.setText("10.0");
		maxRotationZ.setText("10.0");

		quantsize.setText("1000");
		quantnumber.setText("10");

		commands.setText("delay 100000");
	}

	private boolean isValid(){
		String errorMessage ="";
		if (shipEdgeLength.getText() == null || shipEdgeLength.getText().length() == 0) {
	           errorMessage += "Не указана длина!\n";
		}
		if (Double.parseDouble(shipEdgeLength.getText())>100000000){
			   errorMessage += "Длина должна быть меньше 100000000";
		}
		if (shipMass.getText() == null || shipMass.getText().length() == 0) {
	           errorMessage += "Не указана масса!\n";
		}
		if (fuelMass.getText() == null || fuelMass.getText().length() == 0) {
	           errorMessage += "Не указана масса топлива!\n";
		}
		if (maxFuelUsagePerSec.getText() == null || maxFuelUsagePerSec.getText().length() == 0) {
	           errorMessage += "Не указан максимальный расход топлива!\n";
		}
		if (Double.parseDouble(maxFuelUsagePerSec.getText())>1000){
			   errorMessage += "Массовый расход должен быть меньше 1000";
		}
		if (impulsePerFuel.getText() == null || impulsePerFuel.getText().length() == 0) {
	           errorMessage += "Не указан удельный импульс двигателя!\n";
		}
		if (Double.parseDouble(impulsePerFuel.getText())>10000){
			   errorMessage += "Удельный импульс должен быть меньше 10000";
		}
		if (maxOverload.getText() == null || maxOverload.getText().length() == 0) {
	           errorMessage += "Не указана предельная нагрузка!\n";
		}
		if (maxHeating.getText() == null || maxHeating.getText().length() == 0) {
	           errorMessage += "Не указан максимальный нагрев!\n";
		}
		if (orientationX.getText() == null || orientationX.getText().length() == 0 ||
			orientationY.getText() == null || orientationY.getText().length() == 0 ||
			orientationZ.getText() == null || orientationZ.getText().length() == 0) {
		       errorMessage += "Не указана ориентация в пространстве!\n";
		}
		if (Double.parseDouble(orientationX.getText())>360 ||
			Double.parseDouble(orientationY.getText())>360 ||
			Double.parseDouble(orientationZ.getText())>360){
				errorMessage += "Угол должен быть меньше 360";
		}
		if (initialX.getText() == null || initialX.getText().length() == 0 ||
			initialY.getText() == null || initialY.getText().length() == 0 ||
			initialZ.getText() == null || initialZ.getText().length() == 0) {
			   errorMessage += "Не указано положение в пространстве!\n";
		}
		if (maxRotationX.getText() == null || maxRotationX.getText().length() == 0 ||
			maxRotationY.getText() == null || maxRotationY.getText().length() == 0 ||
			maxRotationZ.getText() == null || maxRotationZ.getText().length() == 0) {
			   errorMessage += "Не указан максимальный момент вращения!\n";
		}
		if (Double.parseDouble(maxRotationX.getText())>1000 ||
			Double.parseDouble(maxRotationY.getText())>1000 ||
			Double.parseDouble(maxRotationZ.getText())>1000){
				errorMessage += "Момент должен быть меньше 1000";
		}
		if (quantsize.getText() == null || quantsize.getText().length() == 0 ||
			quantnumber.getText()==null || quantnumber.getText().length() == 0){
			   errorMessage += "Не указан квант!\n";
			}
		int secondsInDay = 86400;
		if (Integer.parseInt(quantsize.getText())*Integer.parseInt(quantnumber.getText())>secondsInDay){
			   errorMessage += "Симуляция должна быть менее одного дня";
		}
		if (errorMessage.length() == 0) {
            return true;
        } else {
            Alert alert = new Alert(AlertType.ERROR);
            alert.setTitle("Ошибка!");
            alert.setHeaderText("Исправьте следующие поля");
            alert.setContentText(errorMessage);
            alert.showAndWait();
            return false;

        }
	}
}
