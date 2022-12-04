package 实验七;

import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;

public class FileIO {
    public static void createdictionary() {
        File dictionary = new File("d:/save");
        File adictionary = new File("d:/save/a");
        File bdictionary = new File("d:/save/b");
        File cdictionary = new File("d:/save/a/c");
        dictionary.mkdir();
        adictionary.mkdir();
        bdictionary.mkdir();
        cdictionary.mkdir();
    }
    public static void createFile() throws Exception {
        String file1="d:/save/a/ecust1.txt";
        File ecust1=new File(file1);
        ecust1.createNewFile();
        String file2="d:/save/b/ecust2.txt";
        File ecust2=new File(file2);
        ecust2.createNewFile();
    }
    public static void writeString() throws Exception {
        FileOutputStream fos1 = new FileOutputStream("d:/save/a/ecust1.txt");
        OutputStreamWriter osw1 = new OutputStreamWriter(fos1, "Unicode");
        osw1.write("华东理工大学ecust");
        osw1.flush();
        FileOutputStream fos2 = new FileOutputStream("d:/save/b/ecust2.txt");
        OutputStreamWriter osw2 = new OutputStreamWriter(fos2, "GBK");
        osw2.write("华东理工大学ecust");
        osw2.flush();
    }

    public static void main(String[] args) throws Exception {
        createdictionary();
        createFile();
        writeString();
    }
}
