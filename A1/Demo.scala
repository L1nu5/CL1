import scala.util.Sorting._
import scala.io.StdIn._
object Demo{
	def main(args : Array[String]){
		val s = readLine
		var arr: Array[Int] = s.split(" ").map(_.toInt)
		quickSort(arr)
		println("Status : " + binSearch(arr,0,arr.length-1,1))
	}

	def binSearch(arr:Array[Int],l:Int,h:Int,key:Int) : Int = {
		var high = h
		var low = l
		var mid:Int = (high + low) / 2;
		
		while(low <= high)
		{
			println("mid : " + arr(mid))
			if(arr(mid) == key)
				return mid
			else if(key >  arr(mid))
				low = mid + 1
			else
				high = mid - 1

			mid = (low + high)/2		
		}

		return -1
	}
}