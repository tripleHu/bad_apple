import java.awt.image.BufferedImage;
import java.io.*;
import javax.imageio.ImageIO;
import java.util.Scanner;
import java.util.Random;
                      

class ImageToFigure //���ļ�ֻ����ͼƬRGB��Ϣת��Ϊtxt�ı�;�˲���Ϊ��һ��������֡�ص�ͼ�ֱ��ʸ�Ϊ80*60���ļ����ĸ�ʽΪ��λ����000001��000002������000360�Դ����ƣ�MFC���õ����ݻ���ô�java�ļ����ɵ�txt�ļ�
{                  //��Ҫ��D���½���SL�����ֵ��ļ��У��ڡ�SL���ļ����½��ļ���Ϊ��1�����ļ��зŽص�ͼ���½��ļ���Ϊ��2�����ļ��з�txt�ļ�
	static int mapArray[][][]= new int[6544][80][60];//��������ֵ�ֱ�Ϊ��ͼƬ������ȡֵ��Χ000001-006544�����ﰴ���Լ���֡�ص�ͼƬ����ȷ���� �����꣬�����ꣻ���鴢����������                               
	        /*
			 * 0	��
			 * 1	1
			 * 2	2
			 * 3	3
			 * 4	4
			 * 5	5
			 * 6	6
			 * 7	7
			 * 8	8
			 * 9	��
			 * 10	��
			 * 11	����
			 * 12	ը��(��)
			 * 13	��(δ����)
			 * 14	����
			 * 15	��(δ����)
			 * */
    static String rootpath="D:\\SL";
	public static void main(String[] args) 
	{
		    for(int i=431;i<=6543;i++){       //�����ס�����֣�0-430��431��6543  ����java�ļ���Ҫ�������μ�0-430����һ�Σ�431��6543���еڶ��Σ�����Ҳ����Ҫ�Ķ���
		    StringBuffer image=new StringBuffer();        
			image=image.append(rootpath);
			image=image.append("\\1\\");
			image=image.append(String.format("%06d", i));
			image=image.append(".bmp");
			String imagelocation=image.toString();

			StringBuffer txt=new StringBuffer();
			txt=txt.append(rootpath);
			txt=txt.append("\\2\\");
			txt=txt.append(String.format("%d", i));
			txt=txt.append(".txt");
			String txtlocation=txt.toString();

            imageoutput(imagelocation,txtlocation);
			//loadtxt(i,txtlocation);
			
			}
			
			 
	}
    public static void imageoutput(String imagelocation,String txtlocation)//BMP�ļ���RGB��Ϣ���Ϊtxt
	{
        File file  = new File(imagelocation);
		File outputFile=new File(txtlocation);
           int[][] result = null;
           try {
                BufferedImage bufImg = ImageIO.read(file);
                int height = bufImg.getHeight();
                int width = bufImg.getWidth();
                result = new int[width][height];

				PrintWriter output=new PrintWriter(outputFile);

                for (int i = 0; i < width; i++) {
                     for (int j = 0; j < height; j++) {
                           result[i][j] = bufImg.getRGB(i, j) & 0xFFFFFF;				 
                           //System.out.print(result[i][j]+" ");
						   output.print(imageredefine(result[i][j])+" ");
						   //output.print((result[i][j])+" ");
                           
                     }
                }
                output.close();
           } catch (IOException e) {e.printStackTrace();}
        
	}

    public static void loadtxt(int i,String txtlocation)//�����ã�������txt����д���ڴ�
	{
         File inputFile=new File(txtlocation);
         try {
         Scanner input=new Scanner(inputFile); 
		 
		 while(input.hasNext()){
		
            for (int j = 0; j < 80; j++) {
                     for (int k = 0; k < 60; k++) {
                       mapArray[i][j][k] =input.nextInt();
					   //System.out.print(mapArray[i][j][k]+" ");
					                              }
								          }
		                             
                      
		                        }
		input.close();
		     }
			 catch (FileNotFoundException e) {e.printStackTrace();}
	}
    public static int imageredefine(int inside)//����RGB��Ϣ������ת��
	{
		switch (inside) {
case 3026478:case 3092271:case 3158064:case 3223857:case 3289650:case 3421236:case 3487029:case 3552822:
case 3618615:case 3684408:case 3750201:case 3815994:case 3947580:case 4013373:case 4079166:case 4144959:
case 4210752:case 4276545:case 4342338:case 4473924:case 4539717:case 4671303:case 4737096:
case 4802889:case 4868682:case 4934475:case 5000268:case 5131854:case 5197647:case 5263440:case 5329233:
case 5395026:case 5460819:case 5526612:case 5592405:case 5723991:case 5789784:
case 5855577:case 5921370:case 5987163:case 6118749:case 6184542:case 6250335:
case 6316128:case 6381921:case 6447714:case 6579300:case 6645093:case 6710886:case 6776679:
case 6842472:case 6974058:case 7039851:case 7105644:
case 7237230:case 7434609:case 7500402:case 7631988:
case 7763574:case 7829367:case 7895160:case 8026746:case 8092539:case 8158332:case 8224125:case 8289918:case 8421504:
case 8487297:case 8553090:case 8618883:case 8684676:case 8750469:case 8882055:case 8947848:case 9013641:
case 9079434:case 9211020:case 9276813:case 9342606:case 9474192:case 9539985:case 9671571:case 9737364:
case 9868950:case 9934743:
	return 13;


case 65793:case 131586:case 197379:case 263172:case 328965:
case 394758:case 460551:case 526344:case 592137:
case 657930:case 723723:case 789516:case 855309:case 921102:
case 1052688:case 1184274:case 1250067:case 1315860:
case 1447446:case 1513239:case 1579032:
case 1644825:case 1710618:case 1776411:case 1842204:
case 1907997:case 1973790:case 2039583:case 2105376:
case 2171169:case 2236962:case 2368548:case 2434341:			
		case 0:case 65538:case 458760:case 262150:
		case 986895:
case 5854809:
case 4867914:
case 2499367:
		return 14;   //��ͼ0-430���ݽ���ɫreturnΪ12,431-6544returnΪ14
              
case 16777215:
case 16645629:
case 16514043:
case 16448250:
case 16316664:
case 16185078:
case 16053492:
case 15921906:
case 15790320:
case 15592941:
case 15461355:
case 15329769:
case 15198183:
case 15000804:
case 14869218:
case 14671839:
case 14408667:
case 14277081:
case 14079702:
case 13882323:
case 13684944:
case 13487565:
case 13224393:
case 13092807:
case 12829635:
case 12632256:
case 12369084:
case 12171705:
case 11974326:
case 11711154:
case 11513775:
case 11250603:
case 11053224:
case 10855845:
case 10526880:
case 10329501:
case 10066329:case 16776447: case 16644862: case 16775935: case 16775679:
case 13486797:
case 14342363:
case 15131622:
case 15723760:
case 15986931:
case 16250360:
case 16513275:

  //��ɫ
		return 0;

		default:
			return new Random().nextInt(8)+1;//���1-8������
/*
			 * 0	��
			 * 1	1
			 * 2	2
			 * 3	3
			 * 4	4
			 * 5	5
			 * 6	6
			 * 7	7
			 * 8	8
			 * 9	��
			 * 10	��
			 * 11	����
			 * 12	ը��(��)
			 * 13	��(δ����)
			 * 14	����
			 * 15	��(δ����)
			 * */
			//16645629Ϊ��,     1052688��0��986895��
		}
	}
}
