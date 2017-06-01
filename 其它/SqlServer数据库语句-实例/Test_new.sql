USE [TEST_DB]
GO
/****** Object:  User [test]    Script Date: 05/14/2016 17:56:53 ******/
CREATE USER [test] FOR LOGIN [test] WITH DEFAULT_SCHEMA=[dbo]
GO
/****** Object:  Table [dbo].[LoginTimes]    Script Date: 05/14/2016 17:56:53 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[LoginTimes](
	[ID] [int] NOT NULL CONSTRAINT [DF__LoginTimes__ID__1B0907CE]  DEFAULT ((1)),
	[Times] [int] NULL CONSTRAINT [DF__LoginTime__Times__1BFD2C07]  DEFAULT ((0)),
	[ByteNum] [bigint] NULL,
	[UpdateTime] [datetime] NOT NULL CONSTRAINT [DF_LoginTimes_UpdateTime]  DEFAULT (getdate()),
	[data] [varbinary](8000) NOT NULL,
	[data2] [varchar](max) NOT NULL,
 CONSTRAINT [PK__LoginTimes__1A14E395] PRIMARY KEY CLUSTERED 
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'����ܵ�½����' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'LoginTimes', @level2type=N'COLUMN',@level2name=N'Times'
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'�����ֽ�����' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'LoginTimes', @level2type=N'COLUMN',@level2name=N'ByteNum'
GO
/****** Object:  StoredProcedure [dbo].[SP_LoginTimes]    Script Date: 05/14/2016 17:56:50 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROC [dbo].[SP_LoginTimes]
    @ByteNum BIGINT,  --�����ֽ���
    --@BinaryData varbinary(8000) --����������Ϣ
    @CharData varchar(max)--����������Ϣ
--WITH ENCRYPTION    --����
AS

--��������
SET NOCOUNT ON
    
    DECLARE @Column int,@BinaryData varbinary(8000)
    SET @Column=0
    set @BinaryData = convert(varbinary(8000),@CharData)
    BEGIN
        SELECT @Column=COUNT(*) from [dbo].[LoginTimes]
        if @Column<=0 
            BEGIN--data2 �ֶ�Ӧ��ɾ����ʹ��data�ֶ�
                INSERT [dbo].[LoginTimes] (Times,ByteNum,data,data2) VALUES (1,@ByteNum,@BinaryData,@CharData)
            END
        else
           BEGIN
                UPDATE [dbo].[LoginTimes] SET Times=Times+1,ByteNum=ByteNum+@ByteNum,data=@BinaryData,
                data2=@CharData,UpdateTime = getdate()
           END

        --����ö���������!!!
        --SELECT ByteNum ByteNum,UpdateTime UpdateTime,data2 data from [dbo].[LoginTimes]
        SELECT ByteNum ByteNum,UpdateTime UpdateTime,convert(varchar(8000),data) data from [dbo].[LoginTimes]
        --SELECT * from [dbo].[LoginTimes]
    END
RETURN 0
GO
