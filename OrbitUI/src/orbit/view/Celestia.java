package orbit.view;

import java.io.BufferedReader;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;

import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;

@XmlRootElement
public class Celestia {
	String path;
	String trajectoryPath;
	String scriptPath;

	public String getPath(){
		return path;
	}

	public String getPathToTrajectory(){
		return trajectoryPath;
	}
	public String getScriptPath(){
		return scriptPath;
	}

	@XmlElement
	public void setPath(String path){
		this.path = path;
		this.scriptPath = this.path + "/start_ru.cel";

	}

	@XmlElement
	public void setPathToTrajectory(String pathToExtra){
		this.trajectoryPath = pathToExtra;
	}

	public void setTimeRate(double rate) throws IOException {
		BufferedReader file = new BufferedReader(new FileReader(this.scriptPath));
	    String line;
	    String script = "";
	    while ((line = file.readLine()) != null){
	    	if (line.contains("timerate")){
	    		line = "timerate {rate " + rate +  "}";
	    	}
	    	script += line + "\n";
	    }
	    file.close();
	    FileOutputStream os = new FileOutputStream(scriptPath);
	    os.write(script.getBytes());
	    file.close();
	    os.close();
	}

	public void setVisualTime(double seconds) throws IOException {
		BufferedReader file = new BufferedReader(new FileReader(this.scriptPath));
	    String line;
	    String script = "";
	    while ((line = file.readLine()) != null){
	    	if (line.contains("wait")){
	    		seconds -= 5; //т.к 5 секунд ушло на привественное сообщение
	    		line = "wait {duration " + seconds +  "}";
	    	}
	    	script += line + "\n";
	    }
	    file.close();
	    FileOutputStream os = new FileOutputStream(scriptPath);
	    os.write(script.getBytes());
	    file.close();
	    os.close();
	}

	public void runCelestia() {
		try {
			if(System.getProperty("os.name").equals("Linux"))
			{
				Runtime.getRuntime().exec("celestia");
			}
		}
		catch (IOException e) {
			e.printStackTrace();
		}
	}


}
