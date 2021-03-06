package commands;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Date;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.filechooser.FileNameExtensionFilter;

public class FileFunctions {

    public String inputFileName,outputFileName,outputFilePath;
    private Date date;
    private FileNameExtensionFilter filter;

    public FileFunctions(String outputFileName, String outputFilePath, FileNameExtensionFilter filter) {
        this.outputFileName = outputFileName;
        this.outputFilePath = outputFilePath;
        this.filter = filter;
    }

    public void writtingToFileRoutine() {
        try {
            JFileChooser chooser = new JFileChooser(outputFilePath);
            chooser.setDialogTitle("Select Configuration File Directory");
            chooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
            if (chooser.showSaveDialog(null) == JFileChooser.APPROVE_OPTION) {
                outputFilePath=chooser.getSelectedFile().getAbsoluteFile().toString();
                date = new Date();
                PrintWriter file = new PrintWriter(new File(chooser.getSelectedFile(), outputFileName));
                
                writingLogic(file);

                file.close();
            } else {

            }

        } catch (IOException e) {
            // do something
        }
        
    }

    public void readingFromFile() {
        try {
            JFileChooser jfc = new JFileChooser(outputFilePath);
            jfc.setDialogTitle("Select a Configuration File");
            jfc.setAcceptAllFileFilterUsed(false);
            jfc.addChoosableFileFilter(filter);

            int returnValue = jfc.showOpenDialog(null);
            if (returnValue == JFileChooser.APPROVE_OPTION) {
                inputFileName=jfc.getSelectedFile().getAbsoluteFile().toString();

                FileReader inputFile = new FileReader(jfc.getSelectedFile().getPath());
                BufferedReader bRead = new BufferedReader(inputFile);

                int numberOfLines = 0;
                String str = "";
                while ((str = bRead.readLine()) != null) {
                    numberOfLines++;
                }

                inputFile = new FileReader(jfc.getSelectedFile().getPath());
                bRead = new BufferedReader(inputFile);
                readingLogic(bRead, numberOfLines);
                bRead.close();
            }
        } catch (IOException e) {

        }
    }

    public String spacesString(int numberOfSpaces) {
        String out = "";
        for (int i = 0; i < numberOfSpaces; i++) {
            out += " ";
        }
        return out;
    }

    public int arrayMaxMemberLength(String[] array) {
        int maxSize = 0;
        for (int i = 0; i < array.length; i++) {
            if (array[i].length() > maxSize) {
                maxSize = array[i].length();
            }
        }
        return maxSize;
    }

    public int arrayMaxMemberLength(String[][] array) {
        int maxSize = 0;
        for (int i = 0; i < array.length; i++) {
            for (int j = 0; j < array[i].length; j++) {
                if (array[i][j].length() > maxSize) {
                    maxSize = array[i][j].length();
                }
            }
        }
        return maxSize;
    }

    public void writingLogic(PrintWriter file) {
        file.println("This has been written to the file");
    }

    public void readingLogic(BufferedReader bRead, int numberOfLines) throws IOException {
        String strTemp = "";
        String str = "";
        int k = 0;
        while ((strTemp = bRead.readLine()) != null) {
            str += strTemp;
            k++;
        }

        if (k != numberOfLines) {
            JFrame frame = null;
            JOptionPane.showMessageDialog(frame, "Invalid file format", "File corrupted", JOptionPane.ERROR_MESSAGE);
            readingFromFile();
        }
    }

    public static boolean isNumeric(String str) {
        try {
            double d = Double.parseDouble(str);
        } catch (NumberFormatException nfe) {
            return false;
        }
        return true;
    }

    public Date getDate() {
        return date;
    }
}
